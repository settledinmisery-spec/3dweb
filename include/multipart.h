#ifndef MULTIPART_H
#define MULTIPART_H

#include "http_types.h"
#include <stddef.h>

typedef struct multipart_part {
    char *name;
    char *filename;
    char *content_type;
    char *data;
    size_t data_len;
    struct multipart_part *next;
} multipart_part;

typedef struct {
    multipart_part *parts;
} multipart_form;

// Parse the full body of a request assuming it's multipart/form-data.
// Requires `req->full_body` to be populated (e.g. by read_full_body)
multipart_form *parse_multipart(http_request *req);
void free_multipart(multipart_form *form);

#endif