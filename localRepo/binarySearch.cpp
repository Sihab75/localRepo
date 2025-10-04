#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

int main () {
    int n, q;
    cin >> n >> q;
    vector <int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    while (q--) {
        int tar;
        cin >> tar;
        int st = 0, end = n - 1;
        bool found = false;
        while (st <= end) {
            int mid = st + (end - st ) / 2;
            if (a[mid] == tar) {
                found = true;
                break;
            } else if (a[mid] > tar) {
                end = mid - 1;
            } else {
                st = mid + 1;
            }
        }
        if (found) {
            cout << "found" << endl;
        } else {
            cout << "not found" << endl;
        }
    }
    return 0;
}