#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

int main () {
    vector <int> a;
    int n;
    cin >> n;
    for (int i = 0; i < n; i ++) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    reverse(a.begin(),a.end());
    for (int v: a) {
        cout << v << ' ';
    }
    cout << '\n';
    return 0;
}