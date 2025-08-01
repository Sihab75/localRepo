#include <iostream>
using namespace std;

 int main () {
    int n;
    cin >> n;
    int k = 1;
    for (int i = 1; i <= n; i++) {

        for (int i = 1; i <= 3; i++){
            cout << k << " ";
            k++;
        }
        cout << "PUM" << endl;
        k++;
    }
    return 0;
 }
