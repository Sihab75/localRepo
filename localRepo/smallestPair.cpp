#include <iostream>
using namespace std;

int smallest_pair(int n, int a[]) {
    int min_sum = a[0] + a[1] + 1;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int current = a[i] + a[j] + (j - i);
            if (current < min_sum) {
                min_sum = current;
            }
        }
    }
    return min_sum;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        int a[105];

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int result = smallest_pair(n, a);
        cout << result << endl;
    }

    return 0;
}
