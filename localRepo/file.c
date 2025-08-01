#include <stdio.h>

int main () {
    FILE *file;
    file = fopen("contanct.txt","a");
    fclose(file);
}