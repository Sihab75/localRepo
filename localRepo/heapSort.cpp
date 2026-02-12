#include <iostream>
using namespace std;
void heapifyMax (int arr[], int i, int n) {
    int large = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[large]) {
        large = left;
    }
    if (right < n && arr[right] > arr[large]) {
        large = right;
    }
    if (large != i) {
        swap (arr[i] , arr[large]);
        heapifyMax (arr, large, n);
    }
}
void heapifyMin (int arr[], int i, int n) {
    int sm = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[sm] > arr[left]) {
        sm = left;
    }
    if (right < n && arr[sm] > arr[right]) {
        sm = right;
    }

    if (sm != i) {
        swap (arr[i], arr[sm]);
        heapifyMin (arr, sm, n);
    }
} 
void heapSortA (int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMin (arr, i, n);
    }
    for (int i = 0; i < n; i++) {
        swap (arr[n - 1], arr[i]);
    }
}
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMax (arr, i, n);
    }
    for (int i = n - 1; i>= 1; i--) {
        swap (arr[0], arr[i]);
        heapifyMax (arr, 0, i);
    }
}

int main () {
    int n;
    cout << "Enter the number of Element : ";
    cin >> n;
    cout << "enter Element : ";
    int arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i];
    heapSort (arr, n);
    for (int i = 0; i < n; i++) cout << arr[i] << ' ';
    cout << endl;
    cout << "enter Element : ";
    for (int i = 0; i < n; i++) cin >> arr[i];
    heapSortA (arr, n);
    for (int i = 0; i < n; i++) cout << arr[i] << ' ';
    return 0;
}