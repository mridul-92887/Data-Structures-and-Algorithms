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
void leftRotate(avltree*& y) {
    avltree* x = y->right;
    avltree* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    y = x;
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
void deleteNode(avltree*& root, int key) {
    if (root == nullptr) {
        return;
    }

    if (key < root->data) {
        deleteNode(root->left, key);
    } else if (key > root->data) {
        deleteNode(root->right, key);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        } else if (root->left == nullptr) {
            avltree* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == nullptr) {
            avltree* temp = root;
            root = root->left;
            delete temp;
        } else {
            avltree* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            root->data = temp->data;
            deleteNode(root->right, temp->data);
        }
    }

    if (root == nullptr) {
        return;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        rightRotate(root);
    } else if (balance > 1 && getBalance(root->left) < 0) {
        leftRotate(root->left);
        rightRotate(root);
    } else if (balance < -1 && getBalance(root->right) <= 0) {
        leftRotate(root);
    } else if (balance < -1 && getBalance(root->right) > 0) {
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
