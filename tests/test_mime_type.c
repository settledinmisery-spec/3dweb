#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../src/mime_type.c"

int main() {
    // Original types
    assert(strcmp(get_mime_type("test.html"), "text/html") == 0);
    assert(strcmp(get_mime_type("test.js"), "application/javascript") == 0);
    assert(strcmp(get_mime_type("test.png"), "image/png") == 0);
    assert(strcmp(get_mime_type("test.mp4"), "video/mp4") == 0);

    // New image types
    assert(strcmp(get_mime_type("test.svg"), "image/svg+xml") == 0);
    assert(strcmp(get_mime_type("test.bmp"), "image/bmp") == 0);
    assert(strcmp(get_mime_type("test.tiff"), "image/tiff") == 0);
    assert(strcmp(get_mime_type("test.tif"), "image/tiff") == 0);

    // New text / document types
    assert(strcmp(get_mime_type("test.csv"), "text/csv") == 0);
    assert(strcmp(get_mime_type("test.md"), "text/markdown") == 0);
    assert(strcmp(get_mime_type("test.rtf"), "application/rtf") == 0);

    // Archives
    assert(strcmp(get_mime_type("test.zip"), "application/zip") == 0);
    assert(strcmp(get_mime_type("test.tar"), "application/x-tar") == 0);
    assert(strcmp(get_mime_type("test.gz"), "application/gzip") == 0);
    assert(strcmp(get_mime_type("test.bz2"), "application/x-bzip2") == 0);
    assert(strcmp(get_mime_type("test.7z"), "application/x-7z-compressed") == 0);
    assert(strcmp(get_mime_type("test.rar"), "application/vnd.rar") == 0);

    // Fonts
    assert(strcmp(get_mime_type("test.woff"), "font/woff") == 0);
    assert(strcmp(get_mime_type("test.woff2"), "font/woff2") == 0);
    assert(strcmp(get_mime_type("test.ttf"), "font/ttf") == 0);
    assert(strcmp(get_mime_type("test.otf"), "font/otf") == 0);
    assert(strcmp(get_mime_type("test.eot"), "application/vnd.ms-fontobject") == 0);

    // Web / Other
    assert(strcmp(get_mime_type("test.wasm"), "application/wasm") == 0);

    // Audio types
    assert(strcmp(get_mime_type("test.m4a"), "audio/mp4") == 0);
    assert(strcmp(get_mime_type("test.flac"), "audio/flac") == 0);

    // Case insensitivity check
    assert(strcmp(get_mime_type("test.SVG"), "image/svg+xml") == 0);
    assert(strcmp(get_mime_type("test.ZiP"), "application/zip") == 0);

    // Edge cases
    assert(strcmp(get_mime_type("test"), "application/octet-stream") == 0);
    assert(strcmp(get_mime_type("test."), "application/octet-stream") == 0); // "test." has empty extension, handled via strcasecmp mismatch
    assert(strcmp(get_mime_type("test.unknown"), "application/octet-stream") == 0);

    printf("All mime_type tests passed.\n");
    return 0;
}
