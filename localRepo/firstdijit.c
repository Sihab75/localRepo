#include <stdio.h>

int main () {
    int n;

    scanf("%d",&n);

    int remainder = n / 1000;

    if (remainder % 2 == 0){
        printf("EVEN\n");
    } else {
        printf("ODD\n");
    }

    return 0;
}