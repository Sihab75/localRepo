#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;
#define endl '\n';

int main () {
    vector <int> a;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    for (int b : a) {
        cout << b << ' ';
    }
    cout << endl;
    return 0;
}