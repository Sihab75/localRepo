#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

int main () {
    vector <int> a;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    
    sort(a.begin(),a.end());
    vector <int> :: iterator it = unique (a.begin(),a.end());
    a.erase(it, a.end());
    for (int i: a) {
        cout << i << ' ';
    }
    return 0;
}