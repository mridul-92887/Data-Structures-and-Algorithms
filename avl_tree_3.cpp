#include <iostream>
using namespace std;

// AVL Tree node structure with modern C++ initialization
struct avltree {
    int data;
    avltree* left = nullptr;  // Pointer initialized to nullptr
    avltree* right = nullptr; // Pointer initialized to nullptr
    int height = 1;           // Height initialized to 1 by default
};

// Max function
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

// Get height
int getHeight(avltree* root) {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}

// Balance factor
int getBalance(avltree* root) {
    if (root == nullptr) {
        return 0;
    }
    return getHeight(root->left) - getHeight(root->right);
}

// Right rotate
void rightRotate(avltree*& y) {
    avltree* x = y->left;
    avltree* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    y = x;
}

// Left rotate
void leftRotate(avltree*& x) {
    avltree* y = x->right;
    avltree* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    x = y;
}

// Insert node
void insert(avltree*& root, int data) {
    if (root == nullptr) {
        root = new avltree();
        root->data = data;
        return;
    }

    if (data < root->data) {
        insert(root->left, data);
    } else if (data > root->data) {
        insert(root->right, data);
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && data < root->left->data) {
        rightRotate(root);
    } else if (balance > 1 && data > root->left->data) {
        leftRotate(root->left);
        rightRotate(root);
    } else if (balance < -1 && data > root->right->data) {
        leftRotate(root);
    } else if (balance < -1 && data < root->right->data) {
        rightRotate(root->right);
        leftRotate(root);
    }
}

// In-order traversal
void inOrder(avltree* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->data << "(h=" << root->height << ") ";
        inOrder(root->right);
    }
}

// Main function to test the AVL Tree
int main() {
    avltree* root = nullptr;

    insert(root, 10);
    insert(root, 20);
    insert(root, 30);
    insert(root, 25);
    insert(root, 5);
    
    cout << "In-order traversal: ";
    inOrder(root);
    cout << endl;

    return 0;
}
