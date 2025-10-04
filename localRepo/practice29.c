#include <stdio.h>

int length (char str[],int len) {
    if (str[len] == '\0') {
        return len;
    }
    return length(str, len + 1);
}

int main () {
    char str[5000];
    scanf("%[^\n]",str);
    int len = length(str,0);
    printf("%d",len);
    return 0;
}