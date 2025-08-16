#include <stdio.h>

int main () {
    char str1[5000];
    scanf("%[^\n]",str1);
    char str2[5000];
    int i = 0;
    while (str1[i] != '\0') {
        str2[i] = str1[i];
        i++;
    }
    str2[i] = '\0';
    printf("%s\n",str2);
    return 0;
}