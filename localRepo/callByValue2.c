#include <stdio.h>

int cob (int a) { 
    return a * a * a;
}

int main () {
    int n;
    scanf("%d",&n);
    int result = cob(n);
    printf("%d^3 = %d",n,result);
    return 0;
}