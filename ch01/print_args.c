#include <stdio.h>

int main(int argc, char **args){
    char **p;
    int i = 0;
    for(p = args; *p != NULL; p++){
        printf("arg[%d] = %s\n", i, *p);
        i ++;
    }
    return 0;
}
