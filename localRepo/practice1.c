#include <stdio.h>

int oneToN (int n,int a) {
    if (a > n) {
        return 0;
    }
    printf("%d ",a);
    return oneToN(n ,a + 1);
}

int nToOne (int n) {
    if (n == 0) {
        return 0;
    }
    printf("%d ",n);
    return nToOne(n-1);
}

int main () {
    int n;
    scanf("%d",&n);
    oneToN(n,1);
    printf("\n");
    nToOne(n);
    return 0;
}