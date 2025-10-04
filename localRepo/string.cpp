#include <iostream>
#include <string>
using namespace std;
#define endl '\n'

int main () {
    string s, q;
    getline (cin, s);
    getline (cin, q);

    int lenS = s.size ();
    int lenQ = q.size ();
    cout << lenS << ' ' << lenQ << endl << s + q << endl;
    char temp = s[0];
    s[0] = q[0];
    q[0] = temp;

    cout << s + " " + q << endl;
    return 0;
}