#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *concat(char *s1, char *s2);
int len(char *s);

int main()
{
    setenv("HELLO", "WORLD", 1);
    printf("HELLO=%s\n", getenv("HELLO"));
}

char *concat(char *s1, char *s2)
{
    int l1 = len(s1);
    int l2 = len(s2);

    char ret[l1 + l2 + 1];
    char *p = ret;
    int offset = 0;
    while (offset < l1)
    {
       *(p + offset) = *(s1 + offset);
       offset++;
    }
    
    while (offset < l1 + l2)
    {
       *(p + offset) = *(s2 + offset - l1);
       offset++;
    }
    ret[l1 + l2 + 1] = '\0';
    return p;
}

int len(char *s)
{
    int length = 0;
    char *p = s;
    while (*p != '\0')
    {
        length++;
        p++;
    }
    return length;
}