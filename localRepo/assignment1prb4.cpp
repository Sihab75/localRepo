#include <iostream>

using namespace std;

int main () {
     
    int R, O, V ,B;

    cin >> R >> O >> V >> B;

    int sub = (R + O + V) - B;

    if (sub > 0) {

        cout << sub << endl;

    } else {

        cout <<"0" << endl;

    }

    return 0;

}