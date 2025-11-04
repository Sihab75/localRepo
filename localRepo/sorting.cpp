#include <iostream>
using namespace std;

void BubbleSort (int arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]){
                swap (arr[j],arr[j + 1]);
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[minIdx] > arr[j]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]); 
    }
}

void insertionSort (int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int peak = arr[i];
        int j = i - 1;
        while (j >= 0 && peak < arr[j]) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = peak;
    }
}
void countingSort (int arr[], int n) {
    int k = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > k) {
            k = arr[i];
        }
    }
    int freq[k+1] = {0};
    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
    }
    for (int i = 1; i <= k; i++) {
        freq[i] += freq[i-1];
    }
    int ans[n];
    for (int i = n - 1; i >= 0; i--) {
        ans[--freq[arr[i]]] = arr[i];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = ans[i];
    }
}

int main () {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    BubbleSort(a, n);
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    selectionSort (a, n);
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    insertionSort(a, n);
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    countingSort(a, n);
    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
    return 0;
}