#include <stdio.h>

int main () {
    char str1[2000];
    char str2[2000];
    scanf("%[^\n]",str1);

    int count = 0;
    while (*(str1 + count) != '\0') {
        *(str2 + count) = *(str1 + count);
        count++;
    }
    *(str2 + count) = '\0';
    printf("%s",str2);
    return 0;
}