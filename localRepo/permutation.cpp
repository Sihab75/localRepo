#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    scanf("%d",&n);
    int a[n];
    int b[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(a, a + n);
    sort(b, b + n);
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            cout << "no" << '\n';
            return 0;
        }
    }
    cout << "yes" << '\n';
    return 0;
}