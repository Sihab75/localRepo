#include <iostream>
#include <string>
using namespace std;

int main () {
    int a;
    int b;
    cin >> a >> b;
    string s;
    cin >> s;
    int n = s.length();
    if (n != (a + b + 1)){
        return 0;
    }
    if (s[a] != '-'){
        cout << "No" << '\n';
        return 0;
    }
    for (int i = 1; i < n; i++) {
        if (i == a){
            continue;
        }
        if (!isdigit(s[i])){
            cout << "No" << '\n';
            return 0;
        }
    }
    cout << "Yes" << '\n';

    return 0;
}