#include <iostream>
#include <string>
using namespace std;
#define endl '\n'

int main () {
    string s, y;
    getline (cin, s);
    getline (cin, y);
    
    if (s < y) {
        cout << s << endl;
    } else {
        cout << y << endl;
    }
    return 0;
}