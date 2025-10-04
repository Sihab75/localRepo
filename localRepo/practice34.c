#include <stdio.h>
#include <stdlib.h>

int main () {
    int n;
    scanf("%d",&n);
    int* arr;
    arr = (int*) malloc (n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d",&arr[i]);
        sum += arr[i];
    }
    printf("%d",sum);
    free(arr);
    return 0;
}