#include <iostream>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;
    node (int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

node* insertBSt (node* root, int val) {
    if (root == nullptr) {
        node* newNode = new node(val);
        return newNode;
    }
    if (val < root->data ) {
        root->left = insertBSt (root->left, val);
    } else if (val > root->data) {
        root->right = insertBSt (root->right, val);
    }
    return root;
}

node* searchBst (node* root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    node* temp = root;
    while (temp != nullptr) {
        if (temp->data == val) {
            return temp;
        } else if (temp ->data > val) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    return nullptr;
}

node* findMin (node* root) {
    if (root == nullptr) {
        return nullptr;
    }
    while (root->left !=nullptr) {
        root = root->left;
    }
    return root;
}


node* deleteBst (node* root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    if (val < root->data) {
        root->left = deleteBst (root->left, val);
    } else if (val > root->data) {
        root->right = deleteBst (root->right, val);
    } else {
        if (root->left == nullptr) {
            node* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == nullptr) {
            node* temp = root->left;
            delete root;
            return temp;
        }
        node* temp = findMin (root->right);
        root->data = temp->data;
        root->right = deleteBst (root->right, temp->data);
    }
    return root;
}

void preOderTraversal (node* root) {
    if (root == nullptr) {
        return;
    }
    cout << root->data << " ";
    preOderTraversal (root->left);
    preOderTraversal (root->right);
}

int main () {
    int n;
    cout << "enter the number of node : ";
    cin >> n;
    cout << "enter node: ";
    node* root = nullptr;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        root = insertBSt (root, x);
    }
    int val;
    preOderTraversal (root);
    cout << endl;
    cout << "enter your search value: ";
    cin >> val;
    node* no = searchBst (root, val);
    cout << no->data << " ==== " << no << endl;
    cout << "Enter delete node :";
    cin >> val;
    root = deleteBst (root, val);
    preOderTraversal (root);
    return 0;
}
