#include <bits/stdc++.h>
using namespace std;

int main () {
    vector <int> a,b;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        b.push_back(x);
    }
    vector <int> final(n + n);
    merge (a.begin(), a.end(), b.begin(), b.end(), final.begin());

    for (int i: final) {
        cout << i << ' ';
    }
    cout << '\n';
    return 0;
}