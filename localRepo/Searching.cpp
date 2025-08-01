#include <iostream>
using namespace std;

int main (){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int target;
    cin >> target;
    for (int i = 0; i < n; i++) {
        if (target == a[i]) {
            cout << i << '\n';
            return 0;
        }
    }
    cout << "-1" << '\n';
    return 0;

    }

