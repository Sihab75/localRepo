#include <stdio.h>

int countAppears (int* a, int n, int count, int x) {
    if (n < 0) {
        return count;
    }
    if (x == *(a + n)) {
        count++;
    }
    return countAppears(a, n - 1, count, x);
}

int main () {
    int n;
    scanf("%d",&n);
    int a[n];
    for (int i = 0; i < n; i++){
        scanf("%d",a + i);
    }
    int x;
    scanf("%d",&x);
    int count = countAppears (a, n - 1, 0,x);
    printf("%d is appears %d time",x,count);
    return 0;
}