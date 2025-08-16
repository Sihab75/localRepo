#include <stdio.h>

int sumOfDigit (int n,int sum) {
    if (n == 0) {
        return sum;
    }

    sum = sum + n % 10;

    return sumOfDigit(n / 10, sum);
}

int main () {
    int n;
    scanf("%d",&n);
    int sum = sumOfDigit (n,0);
    printf("Sum of digit is = %d\n",sum);
    return 0;
}