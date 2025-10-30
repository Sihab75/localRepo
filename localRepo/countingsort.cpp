#include <iostream>
#include <vector>
using namespace std;

int main () {
    int n;
    cin >> n;
    vector <int> arr;
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        arr.push_back (c);
    }
    int k = arr[0];
    for (int i = 1 ; i < n; i++) {
        if (k < arr[i]) {
            k = arr[i];
        }
    }
    vector <int> count (k + 1, 0);
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    for (int i = 1; i <= k; i++) {
        count[i] += count[i- 1];
    }
    vector<int> ans (n);
    for (int i = n - 1; i >= 0; i--) {
        ans[--count[arr[i]]] = arr[i];
    }
    
    for (int val: ans) {
        cout << val << ' ';
    }
    return 0;
}