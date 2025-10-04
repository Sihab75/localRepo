#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    cin >> n;
    int st = 2, end = n - 2;
    while (st <= end) {
        if ( st% 2 == 0 && end % 2 == 0 && (st + end) == n) {
            cout << "YES" << '\n';
            return 0;
        }
        end--;
        st++;
    }
    cout << "NO" << '\n';
    return 0;
}
