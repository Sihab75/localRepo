#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
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

node* buildLevelorderTree (vector <int>& arr, int rootIdx, int n) {
    if (rootIdx >= n) {
        return nullptr;
    }
    node* root = new node(arr[rootIdx]);
    root->left = buildLevelorderTree (arr, 2 * rootIdx + 1, n);
    root->right = buildLevelorderTree (arr, 2 * rootIdx + 2, n);
    return root;
}

void preorderTraversal (node* root) {
    if (root == nullptr) {
        return;
    }
    cout << root->data << ' ';
    preorderTraversal (root->left);
    preorderTraversal (root->right);
}

void inorderTraversal (node* root) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal (root->left);
    cout << root->data << ' ';
    inorderTraversal (root->right);
}

void postorderTraversal (node* root) {
    if (root == nullptr) {
        return;
    }
    postorderTraversal (root->left);
    postorderTraversal (root->right);
    cout << root->data << ' ';
}

void LevelorderTraversal (node* root) {
    if (root == nullptr) {
        return;
    }
    queue <node*> q;
    q.push (root);
    while (!q.empty ()) {
        node* temp = q.front ();
        cout << temp->data << ' ';
        q.pop ();
        if (temp->left != nullptr) {
            q.push (temp->left);
        }
        if (temp->right != nullptr) {
            q.push (temp->right);
        }
    }
    cout << endl;
}

int countNode (node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + countNode(root->left) + countNode (root->right);
}
int countLeaf (node* root) {
    if (root == nullptr) {
        return 0;
    }
    if (root->left == nullptr && root->right == nullptr) {
        return 1;
    }
    return countLeaf (root->left) + countLeaf (root->right);
}
int height (node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + max (height(root->left), height(root->right));
}
int findMax (node* root) {
    if (root == nullptr) {
        return INT_MIN;
    }
    int leftMax = findMax (root->left);
    int rightMax = findMax (root->right);
    return max(root->data, max(leftMax, rightMax));
}
int findMin (node* root) {
    if (root== nullptr) {
        return INT_MAX;
    }
    int leftMin = findMin (root->left);
    int rightMin = findMin (root->right);
    return min(root->data, min (leftMin, rightMin));
}
int main () {
    int n;
    cout << "Enter the number of Node: ";
    cin >> n;
    vector <int> arr (n);
    cout << "Enter the Node : ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    node* root = buildLevelorderTree (arr, 0, n);
    cout << "The tree is (preorder Traversal) : ";
    preorderTraversal (root);
    cout << endl;
    cout << "The tree is (Inorder Traversal): ";
    inorderTraversal (root);
    cout << endl;
    cout << "The tree is (Postorder Traversal) : ";
    postorderTraversal (root);
    cout << endl;
    cout << "The tree is (Levelorder traversal) : ";
    LevelorderTraversal (root);
    cout << "Number of Node in  this tree : " << countNode (root) << endl;
    cout << "Number of Leaf Node in this tree : " << countLeaf (root) << endl;
    cout << "Height of this tree : " << height (root) << endl;
    cout << "Maximum Value in this tree : " << findMax (root) << endl;
    cout << "Minimum Value in this tree : " << findMin (root) << endl;
    return 0;
}