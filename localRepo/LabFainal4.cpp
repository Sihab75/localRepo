#include <iostream>
#include <vector>
using namespace std;

int main () {
    int arr1[8] = {3, 9, 19, 35, 87, 98, 199, 254};
    int arr2[6] = {1, 2, 4, 6,20, 47};
    int arr[14];
    int n1= 8, n2 = 6;
    int n = 14;
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2) {
        if (arr1[i] < arr2[j]) {
            arr[k] = arr1[i];
            k++, i++;
        } else {
            arr[k] = arr2[j];
            j++, k++;
        }
    }
    while (i < n1) {
        arr[k] = arr1[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = arr2[j];
        j++;
        k++;
    }
    for (i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
    return 0;
}