#include <iostream>
using namespace std;

class node{
public:
    int data;
    node* next;
    node(int val) {
        data = val;
        next = nullptr;
    }
};

class linkedList {
    node* head = nullptr;
public :
    void push_back (int val) {
        if (head == nullptr) {
            head = new node(val);
            return;
        }
        node* newNode = new node(val);
        node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void push_front (int val) {
        if (head == nullptr) {
            head = new node (val);
            return;
        }
        node* newNode = new node(val);
        newNode->next = head;
        head = newNode;
    }

    void insertAtPosition (int val, int pos) {
        if (head == nullptr) {
            return;
        }
        node* newNode = new node(val);
        if (pos == 1) {
            newNode->next = head;
            head = newNode;
            return;
        }
        node* temp = head;
        int i = 1;
        while (temp->next != nullptr && i < pos - 1) {
            temp = temp->next;
            i++;
        }
        newNode->next =temp->next; 
        temp->next = newNode;
    }

    void Display () {
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
    void pop_front () {
        if (head == nullptr) {
            return;
        }
        node* temp = head;
        head = head->next;
        delete temp;
    }
    void pop_back () {
        if (head == nullptr) {
            return;
        }
        node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        temp->next = temp->next->next;
    }
    void deleteGivenPosition (int pos) {
        if (head == nullptr) {
            return;
        }
        if (pos == 1) {
            node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        int i = 1;
        node* temp = head;
        while (temp->next != nullptr && i < pos-1) {
            temp = temp->next;
            i++;
        }
        temp->next = temp->next->next;
    }
    node* getMid (node* st, node* end) {
        node* fast = st;
        node* slow = st;
        while (fast != end) {
            fast = fast->next;
            if (fast != end) {
                fast = fast->next;
                slow = slow->next;
            }
        }
        return slow;
    }
    node* binarySeach (int val) {
        if (head == nullptr){
            return nullptr;
        }
        node* st = head;
        node* end = head;
        while (end->next != nullptr) {
            end = end->next;
        }
        while (st->data <= end->data) {
            node* mid = getMid (st, end);
            if (mid->data == val) {
                return mid;
            }
            if (mid->data > val) {
                end = mid;
            } else {
                st = mid->next;
            }
        }
        return nullptr;
    }
    void revers () {
        if (head == nullptr) {
            return;
        }
        node* prev = head;
        node* curr = head->next;
        node* Next = curr->next;
        prev->next = nullptr;
        while (Next != nullptr) {
            curr->next = prev;
            prev = curr;
            curr = Next;
            Next = Next->next;
        }
        curr->next = prev;
        head = curr;
    }
};

int main () {
    linkedList l;
    int n;
    cout << "Enter the Number of node: ";
    cin >> n;
    cout << "Enter the Element : ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        l.push_back (x);
    }
    l.Display ();
    cout << "Enter the Beginning value : ";
    int val;
    cin >> val;
    l.push_front (val);
    l.Display ();
    cout << "Enter your position of inserting : ";
    int pos;
    cin >> pos;
    cout << "Enter your insert Value is : ";
    cin >> val;
    l.insertAtPosition (val, pos);
    l.Display ();
    cout << "Delete beginning : ";
    l.pop_front ();
    l.Display ();
    cout << "Delete and : ";
    l.pop_back ();
    l.Display ();
    cout << "Enter Deleting position : ";
    cin >> pos;
    l.deleteGivenPosition (pos);
    l.Display ();
    cout << "Enter the search val : ";
    cin >> val;
    node* find = l.binarySeach (val);
    cout << "Search val is : " << find->data << " Adders is : " << find;
    l.Display ();
    l.revers ();
    cout << "Revers is : ";
    l.Display ();
    return 0;
}