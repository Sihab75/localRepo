#include <iostream>
using namespace std;

int main () {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    int j = n - 1, i = 0;
    int found = 1;
    while (i < n){
        if (a[i] != a[j]){
            found = 0;
            break;
        }
        j--;
        i++;
    }
    if (found) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }

    return 0;
    
}