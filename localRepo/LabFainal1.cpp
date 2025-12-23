#include <iostream>
#include <vector>
using namespace std;

int main () {
    int n;
    cout << "Enter the Number of Element: ";
    cin >> n;
    vector <int> arr(n);
    cout << "Enter Element : ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j+1] < arr[j]) {
                swap (arr[j], arr[j + 1]);
            }
        }
    }
    for (int val: arr) {
        cout << val << ' ';
    }
    cout << endl;
    return 0;
}