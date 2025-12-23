#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node (int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

Node* insertLevelOrder (vector <int>& arr, int root, int n) {
    if (root >= n) {
        return nullptr;
    }
    Node* temp = new Node(arr[root]);
    temp->left = insertLevelOrder (arr, 2 * root + 1, n);
    temp->right = insertLevelOrder (arr, 2*root+2, n);
    return temp;
}
void levelOrder (Node* root) {
    if (root == nullptr) {
        return;
    }
    queue <Node*> q;
    q.push (root);
    while (!q.empty()) {
        Node* temp = q.front ();
        cout << temp->data << ' ';
        q.pop();
        if (temp->left != nullptr) {
            q.push (temp->left);
        }
        if (temp->right != nullptr) {
            q.push (temp->right);
        }
    }
}
int main () {
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;
    vector <int> arr(n);
    cout << "Enter the node values : ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    Node* root = insertLevelOrder (arr, 0, n);
    cout << "Level-oder Traversal : ";
    levelOrder (root);
    return 0;
}