#include <stdio.h>

int main () {
    char str1[2000],str2[1000];
    printf("Enter first string: ");
    scanf("%[^\n]",str1);
    getchar ();
    printf("Enter second string : ");
    scanf("%[^\n]",str2);
    int i = 0;
    int count = 0;
    while (str1[i] != 0) {
        count++;
        i++;
    }

    int j  = 0;
    while (str2[j] != '\0') {
        str1[count] = str2[j];
        count++;
        j++;
    }
    str1[count] = '\0';
    printf("%s\n",str1);
    return 0;
}