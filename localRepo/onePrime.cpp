#include <iostream>
#include <cmath>
using namespace std;

int main () {

    int n;

    cin >> n;
    
    if(n <= 1) {
            
        cout << "NO" <<endl;
        
        return 0;

    }

    int i = 2;
    int prime = 1;
    while (i <= sqrt(n)) {

        if (n % i == 0) {

            prime = 0;
            break;
        }
        i++;
    }

    if (prime) {

        cout << "YES" <<endl;

    } else {

        cout << "NO" << endl;

    }

    return 0;
}
