#include <iostream>
using namespace std;

long long powerOf2(int x) {
    long long result = 1;
    for (int i = 0; i < x; i++) {
        result *= 2;
    }
    return result;
}

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    int x = a - c;
    int y = b - c;

    long long sum = powerOf2(x) - powerOf2(y);
    cout << sum << '\n';

    return 0;
}