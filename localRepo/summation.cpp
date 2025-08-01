#include <iostream>
using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    int a[n];
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        
        sum = sum + a[i];
    }
    cout << abs(sum) << '\n';
    return 0;
}