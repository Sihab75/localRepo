#include <stdio.h>

int revers (int n,int reversNumber) {
    if ( n == 0) {
        return reversNumber;
    }
    reversNumber = reversNumber * 10 + n % 10;
    
    return revers(n/10,reversNumber);
}

int main () {
    int n;
    scanf("%d",&n);
    int reversNumber = revers(n,0);
    printf("Revers Number is : %d\n",reversNumber);
    return 0;
}