#include <iostream>
#include <cmath>

using namespace std;

int main () {

    int n;

    cin >> n;

    for (int i = 2;i <= n;i++) {

       int prime = 1;
       int j = 2;
       while (j <= sqrt(i)) {

            if (i % j == 0) {

                prime = 0;
                break;

            }

            j++;

       }

       if (prime) {

            cout << i <<" ";

       }

    }

    return 0;

}
