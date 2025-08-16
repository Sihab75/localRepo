#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i =0; i < n; i++) {
        cin >> a[i];
    }
    int maxProfit = 0;
    int bestBuy = a[0];
    for (int i =1; i < n; i++) {
        if (a[i] > bestBuy) {
            maxProfit = max(maxProfit,a[i]-bestBuy);
        }
        bestBuy = min (bestBuy,a[i]);
    }
    cout << maxProfit << '\n';
    return 0;
}
