#include <stdio.h>

int main () {
    char str[20] = "hello";
    char* p = str;

    while (*p) {
        *p = *p - 32;
        p++;
    }
    printf("%s",str);
    return 0;
}