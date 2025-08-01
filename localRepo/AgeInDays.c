#include <stdio.h>

int main () {
    int n;

    scanf("%d",&n);

    int year = n / 365;
    int month = (n % 365) / 30;
    int day = (n % 365) % 30;
    
    printf("%d years\n%d months\n%d days",year,month,day);

    return 0;

}
