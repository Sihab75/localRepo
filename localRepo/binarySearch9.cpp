#include <iostream>
#include <vector>
using namespace std;

int main () {
    int n;
    cin >> n;
    int st = 0, end = n;

    while (st <= end) {
        int mid = st + (end - st)/2;
        if (mid * mid == n) {
            cout << "Yes" << endl;
            return 0;
        } else if (mid * mid > n)  {
            end = mid - 1;
        } else {
            st = mid + 1;
        }
    }
    cout << "No" << endl;
    return 0;
}