#include <iostream>

using namespace std;

int main () {
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++){

        for (int s = n - i; s >= 1;s--) {

            cout << " ";

        }
        for (int j = 1; j <= (i * 2 - 1); j++){
            cout << "*";
        }

        cout << endl;

    }

    return 0;

}
