#include <stdio.h>

int check(int* a, int n)  {
    if (n <= 0) {
        return 1;
    }
    if (*(a + n) < *(a + n - 1))  {
        return 0;
    }
    return check (a, n - 1);
}

int main () {
    int n;
    scanf("%d",&n);
    int a[n];
    for (int i = 0; i < n; i++){
        scanf("%d",a+i);
    }
    int found = check(a,n - 1);
    if (found) {
        printf("array is shorted\n");
    } else {
        printf("array is not shorted\n");
    }
    return 0;
}