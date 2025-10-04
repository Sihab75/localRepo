#include <bits/stdc++.h>
using namespace std;
#define endl '\n';

int main () {
    int n;
    cin >> n;
    int mat[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    int sum1 = 0;
    for (int i = 0; i < n; i++) {
        sum1 += mat[i][i];
    }
    int sum2 = 0;
    int j = n - 1;
    for (int i = 0; i < n; i++) {
        sum2 += mat[i][j];
        j--;
    }
    int sum = abs(sum1 - sum2);
    cout << sum << endl;
    return 0;
}