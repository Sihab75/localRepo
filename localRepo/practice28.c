#include <stdio.h>
#include <string.h>
int check(char str[], int end, int st) {
    if ( st >= end) {
        return 0;
    }
    char temp = str[st];
    str[st] = str[end];
    str[end] = temp;
    return check(str, end - 1, st + 1);
}

int main () {
    char str[5000];
    scanf("%[^\n]",str);
    int len = strlen(str);
    check (str, len - 1, 0);
    printf("%s\n",str);
    return 0;
}