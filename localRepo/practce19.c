#include <stdio.h>

int main () {
    int n;
    scanf("%d",&n);
    int i = 1,sum = 0,pow = 1;
    while (i <= n) {
        sum += i;
        printf("%d + ",i);
        pow = 10;
        i = i * pow + 1;
    }
    printf("\n%d\n",sum);
    return 0;
}