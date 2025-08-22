#include <stdio.h>

void swap(char* str1, char* str2, int len) {
    for (int i = 0; i < len; i++) {
        char temp = *(str1 + i);
        *(str1 + i) = * (str2 + i);
        *(str2 + i) = temp;
    }
}

int main () {
    char str1[5000],str2[5000];
    printf("enter 1st string : ");
    scanf("%[^\n]",str1);
    getchar ();
    printf("Enter 2nd string : ");
    scanf ("%[^\n]",str2);
    getchar ();
    int i = 0;
    while (str1[i] != '\0') {
        i++;
    }

    swap (str1,str2,i);

    printf("string no.1 = %s\n",str1);
    printf("string no.2 = %s\n",str2);
    return 0;
}