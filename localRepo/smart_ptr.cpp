#include <iostream>
#include <memory>
using namespace std;

int main () {
    unique_ptr <int> ptr = make_unique <int> (10);
    cout << "Value : " << *ptr << endl;
    *ptr = 50;
    cout << "Updated Value: " << *ptr << endl;
    unique_ptr <int> ptr2 = move (ptr);
    if (!ptr) {
        cout << "ptr is now empty (ownership transferred)" << endl;
    }
    cout << "Value from ptr2 : " << *ptr2 << endl;
    return 0;
}