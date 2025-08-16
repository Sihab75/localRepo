#include <stdio.h>

int main () {
    int n;
    scanf("%d",&n);

    int a[n];
    for (int i = 0; i < n; i++){
        scanf("%d",a + i);
    }
    int largest = *a;
    for (int i = 1; i < n; i++) {
        if (*(a + i) > largest) {
            largest = *(a + i);
        }
    }
    printf("largest = %d",largest);
    return 0;
}