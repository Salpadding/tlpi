#!/usr/bin/env bash
NAME=$1
gcc "ch01/${NAME}.c" lib/*.c -o "${NAME}.o"
