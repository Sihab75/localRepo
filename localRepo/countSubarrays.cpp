#include <iostream>
using namespace std;

int main () {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int a[n];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int count = 0;
        for (int st = 0; st < n; st++) {
            for (int end  = st; end < n; end++) {
                int found = 1;
                for (int i = st; i < end; i++) {
                    if (a[i] > a[i + 1]) {
                        found = 0;
                        break;
                    }
                }
                if (found) {
                    count++;
                }
            }
        }
        cout << count << '\n';
    }
    return 0;
}