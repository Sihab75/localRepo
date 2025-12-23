#include <iostream>
using namespace std;

int main () {
    int n;
    cout << "Enter the number of element : ";
    cin >> n;
    int arr[n];
    cout << "Enter Element : ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int val;
    cout << "Enter your insert Element : ";
    cin >> val;
    int array1[n+1];
    int i = 0, k = 0;
    int insert = 0;
    while (k <= n) {
        if (i == 0 && val <= arr[i]) {
            array1[k] = val;
            k++;
            insert = 1;
        } else if (!insert && val >= arr[i - 1] && val < arr[i]){
            array1[k] = val;
            k++;
            insert = 1;
        } else {
            array1[k] = arr[i];
            k++;
            i++;
        }
    }
    for (i = 0; i <= n; i++) {
        cout << array1[i] << ' ';
    }
    cout << endl;
    return 0;
}