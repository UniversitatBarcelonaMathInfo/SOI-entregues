#!/bin/bash

export LD_PRELOAD=/$PWD/malloc.so
./malloctest
ls > ji

# For gdb:
#
# gdb ./malloctest
# (gdb) set enviroment LD_PRELOAD=./malloc.so
# (gdb) ... run
