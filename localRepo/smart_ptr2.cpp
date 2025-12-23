#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Student {
public:
    int id;
    string name;
    void Display () {
        cout << "Id : " << id << " , Name: " << name << endl;
    }
};
void TakeOwnerShip (unique_ptr <Student> s) {
    cout << "Inside function: " << endl;
    s->Display ();

    s->id = 251002116;
    s->name = "maria";
    s->Display ();
}
unique_ptr <Student> student (unique_ptr <Student> s) {
    s->id = 251002086;
    s->name = "sihab+marai";
    return s;
}
int main () {
    unique_ptr <Student> s = make_unique <Student> ();
    s->id = 251002084;
    s->name = "Md. Korimul Jaman";
    cout << "Befor function call : " << endl;
    s->Display ();
    //TakeOwnerShip (move(s));
    if (!s) {
        cout << "student pointer is now after function call." << endl;
    }
    s = student (move(s));
    s->Display ();
    return 0;

}