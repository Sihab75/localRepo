#include <iostream>
#include <vector>
using namespace std;

int maximum (vector <int> arr, int i) {
    int maxIdx = 0;
    for (int j =  0; j <= i; j++) {
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

    for (int i = n - 1; i > 0; i--) {
        int maxIdx = maximum (arr, i);
        swap (arr[maxIdx], arr[i]);
    }
    for (int val: arr) {
        cout << val << ' ';
    }
    cout << endl;
    return 0;
}