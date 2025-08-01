#include <stdio.h>

int main () {

    int n;

    scanf("%d", &n);

    int last = n % 10;
    int first;

    while (n > 0) {

        first = n % 10;
        n /= 10;

    }
    
    int sum = first + last;

    printf("%d",sum);

    return 0;

}
