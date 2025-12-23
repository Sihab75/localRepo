#include <iostream>
using namespace std;

int main () {
    int n;
    cout << "Enter the Number of element is : ";
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    bool found = true;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - j; j++) {
            if (arr[j] > arr[j+1]) {
                swap (arr[j], arr[j+1]);
                found = false;
            }
        }
        if (found) {
            break;
        }
    }
    int k;
    cout << "n th Smallest Element of E is : ";
    cin >> k;
    cout << " n th is = " << arr[k-1] << endl;
    return 0;
}