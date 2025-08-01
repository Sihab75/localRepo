#include <iostream>

using namespace std;

int main () {

    int T,M,C,R;

    cin >> T >> M >> C >> R;

    int div = (T * M) / C;
    int remainder = (T * M) % C;
    int total = div * R;
    
    cout << div << " " << remainder << " " << total << endl;

    return 0;

}