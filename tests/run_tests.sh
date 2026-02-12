#!/bin/bash
set -e
# Ensure we are in the tests directory or handle paths relative to repo root
# The previous version had `cd "$(dirname "$0")"` which is good for local execution.
# But let's check where `test_favicon` expects to be run from.
# The incoming change uses `gcc -I./tests/include ...` which implies running from repo root.
# My change used `gcc -I../include ...` which implied running from `tests/`.

# Let's standardize on running from repo root, as that seems to be the convention of the incoming change.

# 1. Run Favicon Test (Incoming)
if [ -f "tests/test_favicon.c" ]; then
    echo "Running Favicon Test..."
    gcc -I./tests/include -I./include -o tests/test_favicon tests/test_favicon.c
    ./tests/test_favicon
    rm tests/test_favicon
    echo "Favicon Test Passed."
fi

# 2. Run Verify Refactor (My Change)
if [ -f "tests/verify_refactor.c" ]; then
    echo "Running Refactor Verification..."
    # Adjust include paths for repo root execution
    # verify_refactor.c includes "../src/server.c", so it expects to be compiled such that ".." works or we need to be careful.
    # If we compile from root:
    # verify_refactor.c has `#include "../src/server.c"` -> this resolves relative to `tests/verify_refactor.c` location?
    # No, #include "..." is relative to the source file. So `tests/verify_refactor.c` including `../src/server.c` looks in `tests/../src/server.c` which is `src/server.c`. Correct.

    # Include paths for headers:
    # `-I./include` finds `httpserver.h`
    # `-I./tests` finds `3ds.h`

    gcc -I./include -I./tests -o tests/verify_refactor tests/verify_refactor.c
    ./tests/verify_refactor
    rm tests/verify_refactor
    echo "Refactor Verification Passed."
fi
