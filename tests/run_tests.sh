#!/bin/bash
set -e
gcc -I./tests/include -I./include -o tests/test_favicon tests/test_favicon.c
./tests/test_favicon
rm tests/test_favicon

gcc -I./tests/include -I./include -o tests/test_sdcard tests/test_sdcard_handler.c
./tests/test_sdcard
rm tests/test_sdcard

gcc -I./tests/include -I./include -o tests/test_rw tests/test_rw_handler.c
./tests/test_rw
rm tests/test_rw

gcc -I./tests/include -I./include -o tests/test_mime tests/test_mime_type.c
./tests/test_mime
rm tests/test_mime
