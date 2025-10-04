#include <stdio.h>
#include <string.h>

int main () {
    char str[5000];
    scanf("%[^\n]", str);
    int len = strlen(str);
    int freq[256] = {0};

    for (int i = 0; i < len; i++) {
        freq[(unsigned)str[i]]++;
    }

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0)
        printf("%c   %d\n",i,freq[i]);
    }
    return 0;
}