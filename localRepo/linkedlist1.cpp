#include <iostream>
using namespace std;

class node {
public:
    int data;
    node* next;
    node (int val) {
        data = val;
        next = nullptr;
    }
};

class Linked_list {
    node* head = nullptr;
public:

    void push_front (int val) {
        node* newNode = new node(val);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        newNode->next = head;
        head = newNode;
    }

    void push_back (int val) {
        node* newNode = new node (val);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    void push_pos (int val, int pos) {
        node* newNode = new node (val);
        if (pos == 1) {
            newNode->next = head;
            head = newNode;
            return;
        }
        if (head == nullptr) {
            cout << "List is Empty" << endl;
            return;
        }
        node* temp = head;
        node* prev = nullptr;
        int i = 1;
        while (i < pos && temp != nullptr) {
            prev = temp;
            temp = temp->next;
            i++;
        }
        prev->next = newNode;
        newNode->next = temp;
    }

    void print () {
        node* temp = head;
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) {
                cout << "->";
            }
            temp = temp->next;
        }
        cout << endl;
    }
};

int main () {
    int n;
    Linked_list l;
    cout << "Enter Number of Node:" ;
    cin >> n;
    cout << "Enter the Element : ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        l.push_back (x);
    }
    l.print();
    int x;
    cout << "enter the value is : " ;
    cin >> x;
    l.push_front (x);
    l.print ();
    int val, pos;
    cout << "Enter the position is : ";
    cin >> pos;
    cout << "Enter the val is : ";
    cin >> val;
    l.push_pos (val, pos);
    l.print ();
    return 0;
}


