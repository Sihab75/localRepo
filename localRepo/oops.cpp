#include <iostream>
using namespace std;

class student {
private:
    string name;
    int id;
    float mark;
public:
    void input () {
        cout << "enter your name is: ";
        getline(cin, name);
        cout << "enter your Id is: ";
        cin >> id;
        cout << "Enter the mark is :";
        cin >> mark;
    }
    void pint() {
        cout << "Student Name is : " << name << endl << "Student ID is :" << id << endl << "Student mark is : " << mark << endl;
    }
};

int main () {
    student s;
    s.input();
    s.pint();
    return 0;
}