#include <stdio.h>

int sumOfDigits (int n,int sum) {
    if (n == 0) {
        return sum;
    }
    sum = sum + n % 10;
    return sumOfDigits(n / 10,sum);

}

int main () {
    int n;
    scanf("%d",&n);
    int sum = sumOfDigits(n,0);
    printf("Sum Of Digits = %d\n",sum);
    return 0;
}