#include <stdio.h>
#include <ctype.h>

int main () {
    char str[5000];
    scanf("%[^\n]",str);

    int count1 = 0;
    int count2 = 0; 
    int i = 0;
    while (str[i] != '\0') {
        char ch = tolower(str[i]);
        if (ch >= 'a' && ch <= 'z') {
            if ((ch == 'a') || (ch == 'e') || (ch == 'o') || (ch == 'u') || (ch == 'i')) {
                count1++;
            } else {
                count2++;
            }
        }
        i++;
    }
    printf("%d number of vowels in a string\n",count1);
    printf("%d number of consonants in a string\n",count2);
    return 0;
}