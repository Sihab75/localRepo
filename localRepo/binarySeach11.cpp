#include <iostream>
#include <vector>
using namespace std;

int main () {
    int n;
    cin >> n;
    vector <int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back (x);
    }
    int st = 0, end = n - 1;
    while (st <= end) {
        int mid = st + (end - st) / 2;
        if (a[mid] - mid != a[0] - 0) {
            end = mid - 1;
        } else {
            st = mid + 1;
        }
    }
    cout << a[0] + st << endl;
    return 0;
}