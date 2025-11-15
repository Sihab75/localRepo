#include <iostream>
#include <vector>
using namespace std;

int LinearSearch (int arr[], int n, int tar) {
    for (int i = 0; i < n; i++) {
        if (tar == arr[i]) {
            return i;
        }
    }
    return -1;
}

int binarySearch(int arr[], int n, int tar) {
    int st = 0, end = n - 1;
    while (st <= end) {
        int mid = st + (end - st) / 2;
        if (arr[mid] == tar) {
            return mid;
        }
        if (arr[mid] > tar) {
            end = mid - 1;
        } else {
            st = mid + 1;
        }
    }
    return -1;
}

int main () {
    int n, tar;
    cin >> n >> tar;
    int arr[n];

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    cout << binarySearch(arr, n, tar) << endl;
    cout << LinearSearch(arr, n, tar) << endl;
    return 0;
}