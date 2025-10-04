#include <bits/stdc++.h>
using namespace std;

void isCheck (vector <vector<char>>& a, int x, int y, int* find) {
    int n = a.size();
    int m = a[0].size();
    if (x < 0 || y < 0 || x >= n || y >= m) {
        return;
    }
    if (a[x][y] == '.') {
        *find = 1;
        return;
    }
    *find = 0;
}
int main () {
    int n,m;
    cin >> n >> m;
    vector <vector <char>> a(n, vector <char> (m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    int ok = 0;
    isCheck (a, x - 1, y, &ok);
    if (ok) {
        cout << "no" << '\n';
        return 0;
    }
    isCheck (a, x - 1, y - 1, &ok);
    if (ok) {
        cout << "no" << '\n';
        return 0;
    }
    isCheck (a, x - 1, y + 1, &ok);
    if (ok) {
        cout << "no" << '\n';
        return 0;
    }
    isCheck (a, x, y - 1, &ok);
    if (ok) {
        cout << "no" << '\n';
        return 0;
    }
    isCheck (a, x, y + 1, &ok);
    if (ok) {
        cout << "no" << '\n';
        return 0;
    }
    isCheck (a, x + 1, y, &ok);
    if (ok) {
        cout << "no" << '\n';
        return 0;
    }
    isCheck (a, x + 1, y - 1, &ok);
    if (ok) {
        cout << "no" << '\n';
        return 0;
    }
    isCheck (a, x + 1, y + 1, &ok);
    if (ok) {
        cout << "no" << '\n';
        return 0;
    }
    cout << "yes" << '\n';
    return 0;
}