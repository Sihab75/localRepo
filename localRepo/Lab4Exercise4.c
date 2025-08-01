#include <stdio.h>

int main () {

    int n;

    scanf("%d",&n);

    int sum = 0;
    int a = 1;
    int i =1;

    while (i <= n) {

        sum += a;
        a = a * 10 + 1;
        i++;

    }

    printf("%d",sum);

}