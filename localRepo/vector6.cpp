#include <bits/stdc++.h>
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
    int count = 0;
    int x;
    cin >> x;
    for (int i : a) {
        if (x == i) {
            count ++;
        }
    } 
    cout << count << '\n';
    return 0;
}