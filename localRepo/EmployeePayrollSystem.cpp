#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class employee{
    int id;
    string name;
    double basicSalary;
    double bonus;
    double tax;
    double netSalary;
public:
    void input () {
        cout << "Enter employee Id is : ";
        cin >> id;
        cin.ignore ();
        cout << "Enter your name is : ";
        getline (cin, name);
        cout << "Enter your Salary is : ";
        cin >> basicSalary;
        cin.ignore ();
    }
    void calculate () {
        bonus = basicSalary * .1;
        tax = basicSalary * .05;
        netSalary = basicSalary + bonus - tax;
    }
    void print () {
        cout << "Name is : " << name << endl;
        cout << "Id is : " << id << endl;
        cout << "Basic Salary is : " << basicSalary << endl; 
        cout << "Bonus Salary is : " << bonus << endl;
        cout << "Tax is : " << tax << endl;
        cout << "Net Salary is : "  << netSalary << endl;
    }
    void writeToFile (ostream &fout) {
        fout.write ((char*)&id, sizeof(id));
        fout.write ((char*)&basicSalary, sizeof(basicSalary));
        fout.write ((char*)&bonus, sizeof (bonus));
        fout.write ((char*)&tax, sizeof (tax));
        fout.write ((char*)&netSalary, sizeof(netSalary));
        int len = name.size();
        fout.write ((char*)&len, sizeof(len));
        fout.write (name.c_str(), len);
    }
    void readFromFile (istream &fin) {
        fin.read ((char*)&id, sizeof(id));
        fin.read ((char*)&basicSalary, sizeof(basicSalary));
        fin.read ((char*)&bonus, sizeof(bonus));
        fin.read ((char*)&tax, sizeof(tax));
        fin.read ((char*)&netSalary, sizeof(netSalary));
        int len;
        fin.read ((char*)&len, sizeof (len));
        name.resize (len);
        fin.read (&name[0], len);
    }
};

class System {
    string fileName;
public:
    System (string file){
        fileName = file;
    }
    void addEmployee () {
        employee em;
        ofstream fout (fileName, ios::binary | ios::app);
        em.input ();
        em.calculate ();
        em.writeToFile (fout);
        fout.close ();
    }
    void printAll () {
        employee em;
        ifstream fin (fileName, ios:: binary);
        while (fin.peek() != EOF && fin.good ()) {
            em.readFromFile (fin);
            em.print();
            cout << "----------" << endl;
        }
    }
};

int main () {
    System s("Employee_data.dat");
    int choice;
    do {
        cout << "1.Add Employee" << endl;
        cout << "2.Show All employee Data" << endl;
        cout << "3. exit" << endl;
        cin >> choice;
        cin.ignore ();
        switch (choice) {
            case 1:
                s.addEmployee ();
                break;
            case 2:
                s.printAll ();
                break;
            default :
                cout << "wrong choice" << endl;
                break;
        }
    } while (choice != 3);
    return 0;
}