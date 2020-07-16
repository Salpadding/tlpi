// 内存布局

#include <stdio.h>
#include <stdlib.h>

// allocated memory = text segment + initialized data segment + uninitialized data segment + stack frames + heap
char gloBuf[65536]; // uninitialized data segment
int primes[] = {2, 3, 5, 7}; // initialized data segment

static int square(int x){
    int result; // stack frames
    result = x * x;
    return result;
}
