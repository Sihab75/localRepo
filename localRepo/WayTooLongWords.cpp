#include <iostream>
#include <string>
using namespace std;
#define endl '\n'

int main () {
    int t;
    cin >> t;
    getchar();
    while (t--) {
        string s;
        getline (cin, s);
        int len = s.size ();
        if (len <= 10) {
            cout << s << endl;
        } else {
            cout << s[0] << len - 2 << s[len - 1] << endl;
        }
    }
    return 0;
}