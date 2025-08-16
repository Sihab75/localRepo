#include <stdio.h>
#include <ctype.h>

int main () {
    char str1[5000],str2[5000],str3[5000];
    scanf("%[^\n]",str1);
    getchar();

    int i = 0;
    while (str1[i] != '\0') {
        str2[i] = toupper(str1[i]);
        str3[i] = tolower(str1[i]);
        i++;
    }
    printf("Lower case : %s\nUpper case : %s\n",str3,str2);
    return 0;
}