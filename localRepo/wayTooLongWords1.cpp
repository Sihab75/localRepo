#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define rep(i, a, b) for(int i = a; i < b; i++)
#define vi vector <int>

int main () {
    string s;
    cin >> s;
    unordered_map <char,int> a;
    rep (i, 0, s.size()) {
        a[s[i]] ++;
    }

    for(auto x : a)
        cout << x.first << " " << x.second << '\n';
}