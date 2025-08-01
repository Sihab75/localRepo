#include <iostream>
using namespace std;

int main () {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > 0){
            a[i] = 1;
        } else if (a[i] < 0) {
            a[i] = 2;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << a[i] << ' ' ;
    }
    cout << '\n';
    return 0;

}