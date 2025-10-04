#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int maximum(int* a, int i, int max, int n) {
    if (i == n) {
        return max;
    }
    if (max < *(a + i)) {
        max = *(a + i);
    }
    return maximum (a, i + 1, max, n);
}

int main () {
    int n;
    scanf("%d",&n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
    int max = maximum (a, 0, a[0], n);
    printf("%d",max);
    return 0;
}