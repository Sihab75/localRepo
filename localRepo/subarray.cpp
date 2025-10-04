#include <bits/stdc++.h>
using namespace std;

int main () {
    string str = "abcde";
    for (int i = 0; i < 5; i++) {
        for (int j = i; j < 5; j++) {
            for (int k = i; k < j; k++) {
                cout << str[k];
            }
            cout << ' ';
        }
        cout << endl;
    }
    return 0;
}