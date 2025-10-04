#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);

    char words[50][51];
    int maxLen = 0;

    for(int i=0; i<n; i++) {
        scanf("%s", words[i]);
        int len = strlen(words[i]);
        if(len > maxLen) maxLen = len;
    }

    for(int i=0; i<n; i++) {
        int spaces = maxLen - strlen(words[i]);
        for(int j=0; j<spaces; j++) printf(" ");
        printf("%s\n", words[i]);
    }
    return 0;
}
