#!/usr/bin/env bash
NAME=$1
DIRNAME=`dirname "${NAME}"`
FILENAME=`basename "${NAME}"`
gcc -O "${NAME}.c"  lib/*.c -o "${FILENAME}.o" -lcrypt 
./"${FILENAME}.o"