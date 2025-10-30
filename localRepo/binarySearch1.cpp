#include <iostream>
#include <vector>
using namespace std;

int main () {
    int n, tar;
    cin >> n >> tar;
    vector <int> a;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back (x);
    }
    int st = 0, end = n - 1;
    int ans = 0;
    while (st <= end) {
        int mid = st + (end - st) / 2;
        if (a[mid] == tar) {
            ans = mid;
            end = mid - 1;
        } else if (a[mid] > tar) {
            end = mid - 1;
        } else {
            st = mid + 1;
        }
    }
    if (!ans) {
        cout << -1 << endl;
        return 0;
    }
    cout << ans << endl;
    return 0;
}