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
        a.push_back(c);
    }
    
    int st = 0, end = n - 1;
    while (st <= end) {
        int mid = st + (end - st) / 2;
        if (a[mid] == tar) {
            cout << "found" << endl;
            return 0;
        } else if (a[mid] > tar) {
            end = mid - 1;
        } else {
            st = mid + 1;
        }
    }
    cout << "not found" << endl;
    return 0;
}