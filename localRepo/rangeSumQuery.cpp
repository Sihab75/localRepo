#include <bits/stdc++.h>
using namespace std;
#define endl '\n';

int main () {
    int n, q;
    cin >> n >> q;
    vector <long long> a;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        a.push_back (x);
    }
    for (int i = 1; i < n; i++) {
        a[i] += a[i - 1];
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        long long sum = a[r - 1] - (l > 1 ? a[l - 2] : 0);
        cout << sum << endl;
    }
    return 0;
}