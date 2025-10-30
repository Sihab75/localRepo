#include <stdio.h> 
int max (int arr[], int i) {
    int maxIdx = 0;
    for (int j = 0; j <= i ;j++) {
        if (arr [maxIdx] < arr[j]) {
            maxIdx = j;
        }
    }
    return maxIdx;
}

int main () {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    for (int i = n - 1; i > 0; i--) {
        int maxIdx = max (arr, i);
        int temp = arr[maxIdx];
        arr[maxIdx] = arr[i];
        arr[i] = temp;
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}