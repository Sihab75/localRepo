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
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }
    printf("max = %d\n",max);
    free(arr);
    return 0;
}