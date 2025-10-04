#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define endl '\n';

int main () {
    vector <int> a;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int v;
        cin >> v;
        a.push_back (v);
    }
    sort(a.begin(),a.end());
    for (int i: a) {
        cout << i << ' ';
    }
    cout << endl;
    return 0;
}