#include "multipart.h"
#include "mem_utils.h"
#include "http_utils.h"
#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// A simple memmem implementation since standard C doesn't have it
static void *memmem_custom(const void *l, size_t l_len, const void *s, size_t s_len) {
    if (s_len == 0) return (void *)l;
    if (l_len < s_len) return NULL;
    const char *cl = (const char *)l;
    const char *cs = (const char *)s;
    for (size_t i = 0; i <= l_len - s_len; i++) {
        if (memcmp(cl + i, cs, s_len) == 0) {
            return (void *)(cl + i);
        }
    }
    return NULL;
}

static char *extract_attribute(const char *header, const char *attr_name) {
    char *pos = strstr(header, attr_name);
    if (!pos) return NULL;
    pos += strlen(attr_name);
    if (*pos != '=' || *(pos + 1) != '"') return NULL;
    pos += 2;
    char *end = strchr(pos, '"');
    if (!end) return NULL;
    size_t len = end - pos;
    char *res = memalloc(len + 1);
    if (res) {
        memcpy(res, pos, len);
        res[len] = '\0';
    }
    return res;
}

multipart_form *parse_multipart(http_request *req) {
    if (!req->content_type || !startWith(req->content_type, "multipart/form-data")) return NULL;
    char *boundary_pos = strstr(req->content_type, "boundary=");
    if (!boundary_pos) return NULL;
    
    char *boundary_val = boundary_pos + 9;
    char boundary[256];
    snprintf(boundary, sizeof(boundary), "--%s", boundary_val);
    size_t boundary_len = strlen(boundary);

    read_full_body(req);
    if (!req->full_body || req->content_length <= 0) return NULL;

    multipart_form *form = memalloc(sizeof(multipart_form));
    if (!form) return NULL;
    form->parts = NULL;
    multipart_part *last_part = NULL;

    char *curr = req->full_body;
    size_t remaining = req->content_length;

    while (remaining > 0) {
        char *b_start = memmem_custom(curr, remaining, boundary, boundary_len);
        if (!b_start) break;
        
        curr = b_start + boundary_len;
        remaining = req->content_length - (curr - req->full_body);

        if (remaining >= 2 && curr[0] == '-' && curr[1] == '-') {
            // End boundary
            break;
        }
        if (remaining >= 2 && curr[0] == '\r' && curr[1] == '\n') {
            curr += 2;
            remaining -= 2;
        }

        // Parse headers of this part
        char *header_end = memmem_custom(curr, remaining, "\r\n\r\n", 4);
        if (!header_end) break;
        
        size_t header_len = header_end - curr;
        char *headers = memalloc(header_len + 1);
        memcpy(headers, curr, header_len);
        headers[header_len] = '\0';

        multipart_part *part = memalloc(sizeof(multipart_part));
        memset(part, 0, sizeof(multipart_part));
        
        char *cd_pos = strstr(headers, "Content-Disposition:");
        if (cd_pos) {
            part->name = extract_attribute(cd_pos, "name");
            part->filename = extract_attribute(cd_pos, "filename");
        }

        char *ct_pos = strstr(headers, "Content-Type:");
        if (ct_pos) {
            ct_pos += 13;
            while (*ct_pos == ' ') ct_pos++;
            char *ct_end = strstr(ct_pos, "\r\n");
            if (ct_end) {
                size_t c_len = ct_end - ct_pos;
                part->content_type = memalloc(c_len + 1);
                memcpy(part->content_type, ct_pos, c_len);
                part->content_type[c_len] = '\0';
            }
        }
        memdel((void**)&headers);

        curr = header_end + 4; // skip \r\n\r\n
        remaining = req->content_length - (curr - req->full_body);

        char *next_b = memmem_custom(curr, remaining, boundary, boundary_len);
        if (next_b) {
            char *data_end = next_b;
            if (data_end > curr && *(data_end - 1) == '\n') data_end--;
            if (data_end > curr && *(data_end - 1) == '\r') data_end--;
            
            part->data_len = data_end - curr;
            part->data = memalloc(part->data_len + 1);
            memcpy(part->data, curr, part->data_len);
            part->data[part->data_len] = '\0'; 
            
            curr = next_b; 
            remaining = req->content_length - (curr - req->full_body);
        } else {
            break;
        }

        if (!form->parts) {
            form->parts = part;
        } else {
            last_part->next = part;
        }
        last_part = part;
    }
    
    return form;
}

void free_multipart(multipart_form *form) {
    if (!form) return;
    multipart_part *p = form->parts;
    while (p) {
        multipart_part *next = p->next;
        if (p->name) memdel((void**)&p->name);
        if (p->filename) memdel((void**)&p->filename);
        if (p->content_type) memdel((void**)&p->content_type);
        if (p->data) memdel((void**)&p->data);
        memdel((void**)&p);
        p = next;
    }
    memdel((void**)&form);
}
