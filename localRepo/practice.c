#include <stdio.h>
#include <string.h>

int re(char str1[], char str2[], int len, int st) {
    if (st >= len) {
        return 0;
    }
    return re(str1 + len,str1 + st,len - 1,st + 1);
}

int main () {
    char str1[500];
    char str2[500];
    fgets(str1,sizeof(str1),stdin);
    int len = strlen(str1);
    int n = re(str1,str2,len,0);
    printf("%s\n",str2);
    return 0;
} 