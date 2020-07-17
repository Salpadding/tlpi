#include <stdio.h>

struct stru{
    int f0;
    int f1;
    struct stru *prev;
};

int main(){
    struct stru *p = calloc(1000, sizeof(struct stru));
    for(int i = 0; i < 1000; i++){
        (*(p+i)).f1 = 1000;
    }
    for(int i = 0; i < 1000; i++){
        printf("f1 = %d\n", (*(p+i)).f1);
    }
    return 0;
}