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
    for (set <int> :: reverse_iterator it = s.rbegin(); it != s.rend(); it++) {
        cout << *it << ' ';
    }
    cout << endl;
    return 0;
}