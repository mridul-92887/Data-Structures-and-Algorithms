#include <iostream>
using namespace std;

// AVL Tree node structure
struct avltree {
    int data;
    avltree* left;
    avltree* right;
    int height;
};

// Max function
int max(int a, int b) { 
    return (a > b) ? a : b;
}

// Get height
int getHeight(avltree* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Balance factor
int getBalance(avltree* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
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
    if (root == NULL) {
        root = new avltree();
        root->data = data;
        root->left = NULL;
        root->right = NULL;
        root->height = 1;
        return;
    }

    if (data < root->data) {
        insert(root->left, data);
    } else if (data > root->data) {
        insert(root->right, data);
    } else {
        return;
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

// Find min value
void minValueNode(avltree* root, avltree*& minRoot) {
    if (root == NULL) {
        minRoot = NULL;
        return;
    }

    avltree* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    minRoot = current;
}

// Delete node
void deleteNode(avltree*& root, int data) {
    if (root == NULL) {
        return;
    }

    if (data < root->data) {
        deleteNode(root->left, data);
    } else if (data > root->data) {
        deleteNode(root->right, data);
    } else {
        if (root->left == NULL || root->right == NULL) {
            avltree* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                delete root;
                root = NULL;
            } else {
                *root = *temp;
                delete temp;
            }
        } else {
            avltree* temp;
            minValueNode(root->right, temp);
            root->data = temp->data;
            deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL) return;

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

// Search
void search(avltree* root, int data) {
    if (root == NULL) {
        cout << data << " not found!\n";
        return;
    }
    if (root->data == data) {
        cout << data << " found!\n";
    } else if (data < root->data) {
        search(root->left, data);
    } else {
        search(root->right, data);
    }
}

// In-order traversal
void inOrder(avltree* root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->data << "(h=" << root->height << ") ";
        inOrder(root->right);
    }
}

// Pre-order traversal
void preOrder(avltree* root) {
    if (root != NULL) {
        cout << root->data << "(h=" << root->height << ") ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Post-order traversal
void postOrder(avltree* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << "(h=" << root->height << ") ";
    }
}

// Free memory
void freeTree(avltree*& root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
        root = NULL;
    }
}

// Main
int main() {
    avltree* root = NULL;
    int choice, value;

    while (true) {
        cout << "\n--- AVL Tree Menu ---\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. In-order Traversal\n";
        cout << "5. Pre-order Traversal\n";
        cout << "6. Post-order Traversal\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                insert(root, value);
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                deleteNode(root, value);
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                search(root, value);
                break;
            case 4:
                if (root == NULL) cout << "Tree is empty\n";
                else {
                    cout << "In-order: ";
                    inOrder(root);
                    cout << endl;
                }
                break;
            case 5:
                if (root == NULL) cout << "Tree is empty\n";
                else {
                    cout << "Pre-order: ";
                    preOrder(root);
                    cout << endl;
                }
                break;
            case 6:
                if (root == NULL) cout << "Tree is empty\n";
                else {
                    cout << "Post-order: ";
                    postOrder(root);
                    cout << endl;
                }
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    freeTree(root);
    cout << "Program exited.\n";
    return 0;
}
