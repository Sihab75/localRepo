#include <iostream>
#include <string>
using namespace std;
#define endl '\n'

int main () {
    string s;
    getline (cin, s);
    for (char ch: s) {
        if (ch == '\\' ) {
            cout << endl;
            return 0;
        }
        cout << ch;
    }
    cout << endl;
    return 0;
}