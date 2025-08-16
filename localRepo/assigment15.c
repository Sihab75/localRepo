#include <stdio.h>

int main () {
    char str1[5000];
    scanf("%[^\n]",str1);
    getchar ();
    int i = 0;
    while (str1[i] != '\0') {
        i++;
    }
    char str2[5000];
    int j = 0;
    i = i - 1;
    while (i >= 0) {
        str2[j] = str1[i];
        j++;
        i--;
    }
    str2[j] = '\0';
    printf("%s\n",str2);
    return 0;
}