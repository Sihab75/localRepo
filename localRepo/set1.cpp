#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    cin >> n;
    multiset <int> ms;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ms.insert(x);
    }
    for (multiset <int> :: iterator it = ms.begin(); it != ms.end(); it = ms.upper_bound(*it)) {
        cout << *it << "====" << ms.count(*it) << endl;
    }
    return 0;
}