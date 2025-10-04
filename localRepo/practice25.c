#include <stdio.h>

int fac(int n, int ans) {
    if ( n <= 0) {
        return ans;
    }
    return fac(n - 1, ans * n);
}

int main () {
    int n;
    scanf("%d", &n);
    printf("%d\n", fac(n,1));
    return 0;
}