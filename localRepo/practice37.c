#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {
    char str[500];
    fgets(str,sizeof(str),stdin);
    str[strcspn(str, "\n")] = 0;
    int i = 0;
    char *word[50];
    char *token = strtok(str," ");
    while (token !=NULL) {
        word[i++] = token;
        token = strtok(NULL, " ");
    }
    for (int j = i - 1; j >= 0; j--) {
        printf("%s",word[j]);
        if (j != 0) 
        printf(" ");
    }
    return 0;
}