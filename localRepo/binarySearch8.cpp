#include <iostream>
#include <vector>
using namespace std;

int main () {
    int n;
    cin >> n;
    int ans = -1, st = 0, end = n;
    while (st <= end) {
        int mid = st + (end - st);
        if (mid * mid == n) {
            ans = mid;
            break;
        } else if (mid * mid > n) {
            end = mid - 1;
        } else {
            ans = mid;
            st = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}