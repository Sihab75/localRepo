#include <stdio.h>

int main () {
    FILE *file;

    file = fopen("contanct.txt", "a");

    if (file == NULL){
        printf("File could not be opened.\n");
        return 0;
    }

    printf("File is opened successfully.\n");

    fclose(file);
    return 0;
}
