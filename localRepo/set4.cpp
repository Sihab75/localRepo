#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    cin >> n;
    set <int> s;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }
    int x;
    cin >> x;
    set <int> :: iterator lb = s.lower_bound(x);
    set <int> :: iterator ub = s.upper_bound(x);
    if (lb != s.end()) {
        cout << x << " is " << *lb << endl ;
    }
    if (ub != s.end()) {
        cout << x << " is " << *ub << endl;
    }
    return 0;
}