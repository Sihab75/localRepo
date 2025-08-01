#include <stdio.h>

int main () {
    int a,b,c,d;

    scanf("%d %d %d %d",&a,&b,&c,&d);

    int result = ((a % 100) * (b % 100) * (c % 100) * (d % 100)) % 100;

    printf("%02d",result);

    return 0;

}
