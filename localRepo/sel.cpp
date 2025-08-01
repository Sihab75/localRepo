#include <iostream>
#include <iomanip>
using namespace std;

int main (){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int x,p;
    cin >> x >> p;
    double ans = (double) (p * 100) / (100 - x);
    cout << fixed << setprecision(2) << ans << '\n';
    return 0;
}