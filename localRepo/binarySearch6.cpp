#include <iostream>
#include <vector>
using namespace std;

int main () {
    int n, tar;
    cin >> n >> tar;
    vector <int> a;
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        a.push_back (c);
    }

    int st = 0, end = n - 1;
    int ans = 0;
    while (st <= end) {
        int mid = st + (end - st) / 2;
        if (a[mid] == tar) {
            ans = a[mid];
            break;
        } else if (a[mid] > tar) {
            end = mid - 1;
        } else {
            ans = a[mid];
            st = mid + 1;
        }
    }
    if (!ans) {
        cout << "not found";
    }
    cout << ans << endl;
    return 0;
}