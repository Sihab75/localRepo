#include <stdio.h>

int maximum (int a[], int n, int max, int i) {
    if (i >= n) {
        return max;
    }
    if (a[i] > max) {
        max = a[i];
    }
    return maximum(a,n,max,i + 1);
}

int main () {
    int n;
    scanf("%d",&n);
    int a[n];
    for (int i = 0; i < n; i++){
        scanf("%d",a + i);
    }
    int m = a[0];
    int max = maximum (a,n,m,1);
    printf("Maximum element = %d\n",max);
    return 0;
}