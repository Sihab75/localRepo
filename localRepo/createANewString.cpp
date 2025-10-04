#include <iostream>
#include <string>
using namespace std;
#define endl '\n'

int main () {
    string s,t;
    getline(cin, s);
    getline(cin, t);
    int lenOfs = s.length();
    int lenOft = t.length();
    string n = s + " " + t;
    cout << lenOfs  << ' ' << lenOft << endl << n << endl;
    return 0;
}

