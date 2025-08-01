#include <stdio.h>

int main () {

    int n;

    scanf("%d",&n);

    int remainder,product = 1;

    while (n > 0) {

        remainder = n %10;
        product *= remainder;
        n  /= 10;

    }

    printf("%d",product);

    return 0;

}
