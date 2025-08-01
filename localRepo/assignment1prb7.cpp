#include <iostream>

using namespace std;

int main () {

    int P,F;

    cin >> P >> F;

    int div = (P * 8) / F;
    int remainder = (P * 8) % F;

    cout << div << " " << remainder << endl;

    return 0;

}