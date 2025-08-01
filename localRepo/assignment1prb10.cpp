#include <iostream>

using namespace std;

int main () {

    int D, G, P, T;

    cin >> D >> G >> P >> T;

    int n = G * P;
    double dis = (3.1416 * D * n) / 100;
    double v = dis / T;
    
    cout << n << " " << dis << " " << v << endl;

    return 0;

}
