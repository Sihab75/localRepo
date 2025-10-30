#include <stdio.h>

int max (int arr[], int n, int i) {
    int maxIdx = i;
    for (int j = i + 1; j < n; j++) {
        if (arr[j] > arr [maxIdx]) {
            maxIdx = j;
        }
    }
    return maxIdx;
}

int main () {
    int n;
    scanf("%d",&n);
    int arr [n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = max (arr, n, i);
        int temp = arr [maxIdx];
        arr[maxIdx] = arr [i];
        arr[i] = temp;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}