#include <stdio.h>

int main () {
    int n;
    scanf("%d", &n);
    int temp = n;
    int last = temp % 10;
    int sum = 0;
    while (temp != 0) {
        sum = last + (temp %10);
        temp /= 10;
    }
    printf("sum = %d\n",sum);
    return 0;
}