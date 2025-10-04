#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

int main () {
    int n,m;
    cin >> n >> m;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int freq[m + 1] = {0};
    for (int i = 0; i < n; i++) {
        freq[a[i]]++;
    }
    int st = 1;
    while (st <= m) {
        cout << freq[st] << endl;
        st++;
    }
    return 0;

}