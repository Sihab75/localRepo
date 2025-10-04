#include <stdio.h>
#include <string.h>

int cane(char str1[], char str2[], int st, int len, int i) {
    if (i == len) {
        return st;
    }
    str1[st] = str2[i];
    return cane(str1, str2, st + 1, len, i + 1);
}
int main () {
    char str1[500];
    char str2[500];
    fgets (str1, sizeof(str1), stdin);
    str1[strcspn(str1, "\n")] = 0;
    fgets (str2, sizeof(str2),stdin);
    int st = strlen(str1);
    int se = strlen(str2);
    int len = cane (str1, str2, st, se, 0);
    printf("%s\n",str1);
    return 0;
}