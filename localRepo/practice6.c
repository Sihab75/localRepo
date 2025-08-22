#include <stdio.h>

int sumOfAll(int* a, int n,int sum) {
    if (n < 0) {
        return sum;
    }
    sum += *(a + n);
    return sumOfAll(a,n - 1,sum);
}

int main () {
    int n;
    scanf("%d",&n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d",a + i);
    }
    int sum = sumOfAll (a, n - 1, 0);
    printf("Sum = %d\n",sum);
    return 0;
}