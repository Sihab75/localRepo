#include <iostream>
#include <vector>
using namespace std;

void countingSort (vector <int>& arr, int n) {
    int k = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] > k) {
            k = arr[i];
        }
    }

    vector <int> freq(k + 1, 0);

    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
    }

    for (int i = 1; i <= k; i++) {
        freq[i] += freq[i - 1];
    }
    
    vector <int> ans (n);
    for (int i = n - 1; i>= 0; i--) {
        ans[n - freq[arr[i]]] = arr[i];
    }

    for (int i = 0; i < n; i++) {
        arr[i] = ans[i];
    }

}

int main () {
    int n;
    cin >> n;
    vector <int> arr (n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    countingSort (arr, n);

    for (int val: arr) {
        cout << val << ' ';
    }
    cout << endl;
    return 0;
}