#include <iostream>
#include <vector>
using namespace std;

int main () {
    int n, tar;
    cin >> n >> tar;
    vector <int> a;
    for (int i = 0; i <n; i++) {
        int c;
        cin >> c;
        a.push_back (c);
    }
    int first = 0, last = 0;
    int st = 0, end = n - 1;

    while (st <= end) {
        int mid = st + (end - st)/2;
        if (a[mid] == tar) {
            first = mid;
            end = mid - 1;
        } else if (a[mid] > tar) {
            end = mid - 1;
        } else {
            st = mid + 1;
        }
    }
    st = 0, end = n - 1;
    while (st <= end) {
        int mid = st + (end - st)/2;
        if (a[mid] == tar) {
            last = mid;
            st = mid + 1;
        } else if (a[mid] > tar) {
            end = mid - 1;
        } else {
            st = mid + 1;
        }
    }
    if (!first) {
        cout << - 1 << endl;
        return 0;
    }
    cout << (last - first + 1) << endl;
    return 0;
}