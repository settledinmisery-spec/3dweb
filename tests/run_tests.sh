#!/bin/bash
set -e
cd "$(dirname "$0")"
gcc -I../include -I. verify_refactor.c -o verify_refactor
./verify_refactor
rm verify_refactor
