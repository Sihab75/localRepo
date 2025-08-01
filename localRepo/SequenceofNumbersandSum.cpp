#include <iostream>

using namespace std;

int main () {


    while (1) {

        int a,b,sum = 0;

        cin >> a >> b;

        if (a <= 0 || b <= 0) {

            return 0;
        }

        if (a < b) {

            for (int i = a;i <= b;i++) {

                cout << i << " ";

                sum +=i;

            }

        } else {

            for (int i = b ; i <= a ; i++) {

                cout << i << " ";

                sum +=i;

            }


        }

            cout << " sum =" << sum << endl;

    }

    return 0;

}
