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

    int a;
    cin >> a;

    bool found = s.find(a) != s.end();

    if (found)
    cout << "yes" << endl;
    else
    cout << "no" << endl;
    return 0;
}