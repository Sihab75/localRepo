#include <iostream>
using namespace std;

int main () {
    int n;
    cin >> n;
    int limit = 1<<n;
    for (int i=0;i<limit;i++) {
        int gray = i^(i>>1);
        for (int b=n-1;b>=0;b--) {
            cout << ((gray>>b)&1);
        }
        cout << endl;
    }
    return 0;
}