#include <iostream>
#include <vector>
using namespace std;

int main () {
    int n;
    cin >> n;
    vector <int> a;
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        a.push_back (c);
    }
    int st = 0, end = n - 1;
    while (st < end) {
        int mid = st + (end - st) / 2;
        if (a[mid] > a[end]) {
            st = mid + 1;
        } else {
            end = mid;
        }
    }
    cout << a[st] << endl;
    return 0; 
}