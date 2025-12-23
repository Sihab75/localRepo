#include <iostream>
#include <vector>
using namespace std;

int main () {
    int n;
    cout << "Enter the number of Element : ";
    cin >> n;
    vector <int> arr(n);
    cout << "Enter the Element : ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i < n ; i++) {
        int j = i - 1;
        int peek = i;
        while (j >= 0 && arr[peek] < arr[j]) {
            swap (arr[peek], arr[j]);
            peek--;
            j--;
        }
    }
    for (int val: arr) {
        cout << val << ' ';
    }
    return 0;
}