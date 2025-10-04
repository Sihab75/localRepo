#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

int main () {
    string s;
    getline (cin, s);

    int st = 0, end = s.length() - 1;

    while (st <= end) {
        if (s[st] != s[end]) {
            cout << "NO" << endl;
            return 0;
        }
        st++, end --;
    }
    cout << "YES" << endl;
    return 0;
}