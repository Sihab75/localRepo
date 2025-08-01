#include <iostream>
#include <iomanip>

using namespace std;

int main (){

    int D,N;

    cin >> D >> N;

    double  dis = 3.1416 * D * N;

    cout << fixed << setprecision(2) << dis << endl;

    return 0;

}
