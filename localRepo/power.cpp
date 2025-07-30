#include <iostream>
using namespace std;
long long powOf2(int binForm) {
    if (binForm == 0){
        return 1;
    }
    long long pow = 1 , x = 2;
    if (binForm < 0) {
        x = 1 / x;
        binForm = - binForm;
    }
    while (binForm > 0) {
        if (binForm % 2 == 1) {
            pow *= x;
        }
        x *= x;
        binForm /= 2;
    }
    return pow;
}
int main () {
    int a,b,c;
    cin >> a >> b >> c;
    int x = a - c;
    int y = b - c;
    int sum = powOf2(x)  - powOf2(y);
    cout << sum << '\n';
    return 0;
}