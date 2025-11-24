#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class student {
    string name;
    int id;
    float cgpa;
    string dept;
public:
    void input() {
        cout << "Enter Id: " ;
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Department: ";
        getline (cin, dept);
        cout << "Enter CGPA : ";
        cin >> cgpa;
        cin.ignore ();
    }
    void print () {
        cout << "Student Name : " << name << endl;
        cout << "Student Id : " << id << endl;
        cout << "Department : "  << dept << endl;
        cout << "CGPA : " << cgpa << endl;
    }
    int getId () {
        return id;
    }
    void setCGPA (float mark) {
        cgpa = mark;
    }
    void writeToFile (ostream &fout) {
        fout.write ((char*)&id, sizeof(id));
        fout.write ((char*)&cgpa, sizeof(cgpa));
        int len = name.size ();
        fout.write ((char*)&len, sizeof(len));
        fout.write (name.c_str(), len);
        len = dept.size ();
        fout.write ((char*)&len, sizeof(len));
        fout.write (dept.c_str(), len);
    }
    void readFromFile (istream &fin) {
        fin.read ((char*)&id, sizeof(id));
        fin.read ((char*)&cgpa, sizeof(cgpa));
        int len;
        fin.read ((char*)&len, sizeof(len));
        name.resize (len);
        fin.read (&name[0], len);
        fin.read ((char*)&len, sizeof(len));
        dept.resize (len);
        fin.read (&dept[0], len);
    }
};

class studentManagement {
    string fileName;
public:
    studentManagement (string file) {
        fileName = file;
    }

    void addStudent () {
        student s;
        s.input ();
        ofstream fout (fileName, ios::binary | ios::app);
        s.writeToFile (fout);
        fout.close();
        cout << "Student added successfully." << endl;
    }
    void printAll () {
        student s;
        ifstream fin (fileName, ios::binary);
        while (fin.peek() != EOF && fin.good()) {
            s.readFromFile (fin);
            s.print ();
            cout << "-----------" << endl;
        }
        fin.close ();
    }
    void searchByID(int id) {
        student s;
        ifstream fin (fileName, ios::binary);
        while (fin.peek() != EOF && fin.good()) {
            s.readFromFile (fin);
            if (s.getId()== id) {
                cout << "Student found: " << endl;
                s.print();
                fin.close ();
                return;
            }
        }

        cout << "Student with id: " << id << "not found" << endl;
        fin.close();
    }
    void updateMarks (int id, float marks) {
        student s;
        fstream file (fileName, ios::binary|ios::in|ios::out);
        while (file.peek() != EOF && file.good()){
        streampos pos = file.tellg ();
        s.readFromFile (file);
            if (s.getId () == id) {
                s.setCGPA (marks);
                file.seekp (pos);
                s.writeToFile (file);
                file.close ();
                return;
            }
        }
    }

    void deleteStudent (int id) {
        student s;
        ifstream fin (fileName, ios::binary);
        ofstream fout ("temp.dat", ios::binary);
        while (fin.peek() != EOF && fin.good()) {
            s.readFromFile (fin);
            if (s.getId () != id) {
                s.writeToFile (fout);
            }
        }
        fin.close ();
        fout.close ();
        remove (fileName.c_str ());
        rename ("temp.dat", fileName.c_str());
    }

};

int main () {
    studentManagement s("students.dat");
    int choice;
    do {
        cout << endl << "1.Add Student" << endl;
        cout << "2.Show All Student " << endl;
        cout << "3.Search Student" << endl;
        cout << "4.Update CGPA" << endl;
        cout << "5.Delete Student" << endl;
        cout << "6.Exit" << endl;
        cout << "Enter Choice" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
            s.addStudent ();
            break;
            case 2:
                s.printAll ();
                break;
            case 3:
                int id;
                cout << "Enter Your Student id is:" << endl;
                cin >> id;
                cin.ignore ();
                s.searchByID (id);
                break;
            case 4:
                cout << "Enter Student Id is:" << endl;
                cin >> id;
                cin.ignore ();
                cout << "Enter CGPA is : " ;
                float cgpa;
                cin >> cgpa;
                s.updateMarks (id,cgpa);
                break;
            case 5:
                cout << "Enter Student Id is: ";
                cin >> id;
                cin.ignore ();
                s.deleteStudent (id);
                break;
            default:
                cout << "Wrong choice" << endl;
                break;
        }
    } while (choice != 6);
    return 0;
}