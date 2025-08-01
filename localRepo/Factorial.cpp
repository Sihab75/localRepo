#include <iostream>

using namespace std;

int main () {

    int n,f;

    cin >> n;

    for (int i = 1;i <= n;i++){

        cin >> f;
        long long int factorial = 1;

        for (int j = 1;j <= f;j++){

            factorial = factorial *j;
        }

        cout << factorial << endl;

    }

    return 0;

}
