#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main () {
    char s[5000];
    scanf("%[^\n]",s);
    int length = strlen(s);
    int count = 0;
    for (int i = 0; i < length; i++) {
        char ch = *(s + i);
        ch = tolower(ch);
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            count++;
        }
    }
    printf("count = %d\n",count);
    return 0;
}