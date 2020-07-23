#!/usr/bin/env bash
DIR=`dirname $0`
gcc "${DIR}/main.c" -o "${DIR}/main.o"
"${DIR}/main.o"