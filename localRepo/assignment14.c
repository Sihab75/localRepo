#include <stdio.h>

int main () {
    char str1[5000];
    char str2[5000];
    printf("Enter 1st string : ");
    scanf("%[^\n]",str1);
    getchar();
    printf("Enter 2nd string : ");
    scanf("%[^\n]",str2);
    getchar ();
    int i = 0;
    int found = 1;
    while (str1[i] != '\0' || str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            found = 0;
            break;
        }
        i++;
    }
    if (found) {
        printf("1st string = 2nd string\n");
    } else {
        printf("1st string != 2nd string\n");
    }
    return 0;
}