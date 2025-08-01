#include <iostream>

using namespace std;

int main () {

    for(int row = 1 ; row <= 4 ; row ++) {

        for (int col = 1 ; col <= 4 ; col ++) {

            if (row == 1 || row == 4 || col == 1 || col == 4) {

                cout << "*" << " ";
                
            } else {

                cout << " " << " ";

            }
        }

        cout << endl;

    }

    return 0;

}
