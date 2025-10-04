#include <iostream>
#include <string>
using namespace std;
#define endl '\n'

int main () {
    string s;
    getline (cin, s);
    long long sum = 0;
    for (char ch: s) {
        sum += ch - '0';
    }
    cout << sum << endl;
    return 0;
}