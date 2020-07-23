#!/usr/bin/env bash
OPT=""

if [ `uname` != "Darwin" ]; then
    OPT="-lcrypt"
fi

NAME=$1
DIRNAME=`dirname "${NAME}"`
FILENAME=`basename "${NAME}"`
gcc -pthread "${NAME}.c"  lib/*.c -o "${FILENAME}.o"
./"${FILENAME}.o"
