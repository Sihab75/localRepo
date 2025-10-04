#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

int main () {
    int t;
    cin >> t;
    getchar ();
    while (t--) {
        string s;
        getline(cin, s);

        if (s.find("010") != string::npos || s.find("101") != string::npos) {
            cout << "Good" << endl;
        } else {
            cout << "Bad" << endl;
        }
    }
    return 0;
}