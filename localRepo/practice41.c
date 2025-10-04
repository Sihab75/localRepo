#include <stdio.h>
#include <string.h>

FILE *fptr;

void digits (char str[],int n) {
    fptr = fopen("digits.txt", "w");
    for (int i = 0; i < n; i++) {
        if(str[i] >= '0' && str[i] <= '9') {
            fprintf(fptr, "%c",str[i]);
        }
    }
    fclose(fptr);
}

void non_digits (char str[], int n) {
    fptr = fopen ("non_digits.txt", "w");
    for (int i = 0; i < n; i++) {
        if(!(str[i] >= '0' && str[i] <= '9')) {
            fprintf(fptr, "%c",str[i]);
        }
    }
    fclose(fptr);
}


int main () {
    char str[5000];
    scanf("%[^\n]",str);
    int len = strlen(str);
    digits(str, len);
    non_digits(str,len);
    return 0;
}