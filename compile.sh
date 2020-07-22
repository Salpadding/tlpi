#!/usr/bin/env bash
NAME=$1
DIRNAME=`dirname "${NAME}"`
FILENAME=`basename "${NAME}"`
gcc "${NAME}.c"  lib/*.c -o "${FILENAME}.o" -lcrypt 
