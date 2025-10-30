#include <stdio.h>

int minimum (int arr[], int i) {
    int minIdx = 0;
    for (int j = 1; j <= i; j++) {
        if (arr[minIdx] > arr[j]) {
            minIdx = j;
        }
    }
    return minIdx;
}

int main () {
    int n;
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (int i = n - 1; i > 0; i--) {
        int minIdx = minimum (arr, i);
        int temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr [i] = temp;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}