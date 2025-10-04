#include <bits/stdc++.h>
using namespace std;
#define endl '\n';

int main (){
    int a,b;
    cin >> a >> b;
    int mar[a][b];
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            cin >> mar[i][j];
        }
    }
    int x;
    cin >> x;
    int found = 1;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (x == mar[i][j]) {
                found = 0;
                break;
            }
        }
        if (!found)
        break;
    }
    if (found) {
        cout << "will take number" << endl;
    } else {
        cout << "will not take number" << endl;
    }
    return 0;
}