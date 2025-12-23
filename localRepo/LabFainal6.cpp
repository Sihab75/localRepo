#include <iostream>
using namespace std;

int main () {
    int n;
    cout << "Enter the Number of Element : ";
    cin >> n;
    int arr[n];
    cout << "Enter Element is : ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int Idx = 0;
    int val;
    cout << "Enter the Deleting Element is : ";
    cin >> val;
    int st = 0, end = n - 1;
    while (st <= end) {
        int mid = st + (end - st) / 2;
        if (val == arr[mid]) {
            Idx = mid;
            break;
        } else if (val < arr[mid]) {
            end = mid - 1;
        } else {
            st = mid + 1;
        }
    }
    if (!Idx) {
        cout << "Element is Not fond" << endl;
        return 0;
    }
    for (int i = Idx; i < n - 1; i++) {
        arr[i] = arr[i+1];
    }
    for (int i = 0; i < n - 1; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
    return 0;
}