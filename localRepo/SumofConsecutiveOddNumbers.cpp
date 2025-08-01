#include <iostream>

using namespace std;

int main () {

    int n;

    cin >> n;

    for (int i = 1;i <= n;i++) {

        int a,b,sum = 0;

        cin >> a >> b;

            if (a > b){

                swap (a,b);
            }

            for (int i = a + 1;i < b;i++){

                if (i % 2 != 0){

                    sum += i;

                }

            }



        cout << sum << endl;

    }

    return 0;

}
