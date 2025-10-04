#include <bits/stdc++.h>
using namespace std;

int main () {
    string s;
    getline (cin, s);
    map <char, int> freq;
    for (char ch: s) {
        freq[ch]++;
    }
    for (map <char, int> :: iterator it = freq.begin(); it != freq.end();it++) {
        cout << it->first << ':' << it -> second << endl;
    }
    return 0;
}