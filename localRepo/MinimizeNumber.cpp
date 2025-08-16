#include <iostream>
using namespace std;

int main () {
    int n;
    cin >> n;
    int a[n];                                                                                                                                                                      
    for (int i=0; i < n; i++) {
        cin >> a[i];
    }
    int count = 0,found = 0;
    while (1) {
        for (int i = 0; i < n; i++) {
            if (a[i] % 2 != 0) {
                found = 1;
                break;
            }
        }
        if (found) {
            break;
        }
        for (int i = 0; i < n; i++) {
            a[i] = a[i] / 2;
        }
        count++;
    }
    cout << count << '\n';
    return 0;
}