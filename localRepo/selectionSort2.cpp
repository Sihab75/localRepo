#include <iostream>
#include <vector>
using namespace std;

int maximum (vector <int> arr, int i, int n) {
    int maxIdx = i;
    for (int j = i + 1; j < n; j++) {
        if (arr[maxIdx] < arr[j]) {
            maxIdx = j;
        }
    }
    return maxIdx;
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

    for (int i = 0; i < n - 1; i++) {
        int maxIdx = maximum (arr, i, n);
        swap (arr[maxIdx], arr[i]);
    }
    for (int val: arr) {
        cout << val << ' ';
    }
    cout << endl;
    return 0;
}