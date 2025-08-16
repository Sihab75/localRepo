#include <stdio.h>

int main () {
    char str[5000];
    scanf("%[^\n]",str);
    int i = 0;
    int len = 0;
    while (str[i] != '\0') {
        len++;
        i++;
    }
    printf("%d\n",len);
    return 0;
}