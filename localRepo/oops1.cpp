#include <iostream>
using namespace std;

class Rectangle {
private:
    double len;
    double wight;
public:
    void input () {
        cout << "Enter The length of Rectangle is : " ;
        cin >> len;
        cout << "Enter The Wight of Rectangle is : ";
        cin >> wight;
    }
    double area () {
        return len * wight;
    }
    double perimeter () {
        return 2 * (len + wight);
    }
};

int main () {
    Rectangle r;
    r.input ();
    int ara = r.area ();
    int peri = r.perimeter ();
    cout << ara << endl << peri << endl;
    return 0;
}