#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    cin >> n;
    set <int> s;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        s.insert(a);
    }
    int x;
    cin >> x;
    s.erase(x);

    for (set <int> :: iterator it = s.begin(); it != s.end(); it++) {
        cout << *it << endl;
    }
    return 0;
}