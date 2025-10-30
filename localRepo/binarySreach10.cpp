#include <iostream>
#include <vector>
using namespace std;
int pik = rand() % 100 + 1;
int guess (int num) {
    if (num == pik) {
        return 0;
    } else if (num > pik) {
        return -1;
    } else {
        return 1;
    }
}

int main () {
    int n;
    cin >> n;
    int st = 0, end = n;
    while (st <= end) {
        int mid = st + (end - st) / 2;
        int res = guess (mid);
        if (res == 0) {
            cout << mid << endl;
            return 0;
        } else if (res == -1) {
            end = mid - 1;
        } else {
            st = mid + 1;
        }
    }
    cout << -1 << endl;
    return 0;
}