#include <bits/stdc++.h>
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
    int Max = INT_MIN;
    int sMax = INT_MIN;
    for (int i: a) {
        if (Max < i) {
            sMax = Max;
            Max = i;
        } else if (sMax < i) {
            sMax = i;
        }
    }

    cout << "second Max = " << sMax << '\n';
    return 0;
} 