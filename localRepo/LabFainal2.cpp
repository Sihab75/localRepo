#include <iostream>
#include <vector>
using namespace std;

int main () {
    int n;
    cout << "Enter Number of Element : ";
    cin >> n;
    vector <int> arr(n);
    cout << "Enter the Element : ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap (arr[i], arr[minIdx]);
    }
    for (int val: arr)
        cout << val << ' ';
    cout << endl;
    return 0;
}