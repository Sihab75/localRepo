#include <iostream>

using namespace std;

int main () {

    int n;
    
    cin >> n;

    long long  sum = n * (n + 1) / 2;

    cout << sum << endl;

    return 0;
}