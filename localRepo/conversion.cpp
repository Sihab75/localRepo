#include <iostream>
#include <string>
using namespace std;
#define endl '\n'

int main () {
    string s;
    getline (cin, s);

    for (char ch: s) {
        if (isupper(ch)) {
            cout << (char) tolower(ch) ;
        } else if (ch == ',') {
            cout << ' ';
        } else if (islower(ch)) {
            cout << (char) toupper(ch) ;
        } else {
            cout << ch;
        }
    }
    cout << endl;
    return 0;
}