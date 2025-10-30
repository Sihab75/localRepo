#include <iostream>
#include <vector>
using namespace std;

int minimum (vector <int> arr, int i) {
    int minIdx = 0;
    for (int j = 0; j <= i; j++) {
        if (arr[minIdx] > arr[j]) {
            minIdx = j;
        }
    }
    return minIdx;
}

int main () {
    int n;
    cin >> n;
    vector <int> arr;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        arr.push_back (x);
    }

    for (int i = n - 1; i > 0; i--) {
        int minIdx = minimum (arr, i);
        swap (arr[minIdx], arr[i]);
    }
    for (int val: arr) {
        cout << val <<  ' ';
    }
    cout << endl;
    return 0;
}