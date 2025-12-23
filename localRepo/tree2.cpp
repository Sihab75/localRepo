#include <iostream>
using namespace std;

class node {
public:
    int data;
    node* right;
    node* left;
    node (int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

node* buildTre () {
    int x;
    cin >> x;
    if (x == -1) {
        return nullptr;
    }
    node* root = new node(x);
    root->left = buildTre ();
    root->right = buildTre ();
    return root;
}
void inorderTraversal (node* root) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal (root->left);
    cout << root->data << ' ';
    inorderTraversal (root->right);
}

int main () {
    cout << "enter nodes in Preorder (-1 for Null): ";
    node* root = buildTre ();
    cout << "Inorder traversal:";
    inorderTraversal (root);
    return 0;
}