#include <iostream>
using namespace std;

// AVL Tree er node structure
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Max function for height calculation
int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}

// Height function for each node
int getHeight(struct Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

// Balance factor calculation
int getBalance(struct Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// New node create korar function
void createNode(struct Node *&node, int key)
{
    node = new Node;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Initial height of new node is 1
}

// Right rotation for balancing
void rightRotate(struct Node *&y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    y = x; // Set new root
}

// Left rotation for balancing
void leftRotate(struct Node *&x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    x = y; // Set new root
}

// Insert function with balancing and rotation
void insert(struct Node *&node, int key)
{
    // If the node is NULL, create a new node
    if (node == NULL)
    {
        createNode(node, key);
        return;
    }

    // Insert key into the left or right subtree based on comparison
    if (key < node->key)
    {
        insert(node->left, key);
    }
    else if (key > node->key)
    {
        insert(node->right, key);
    }
    else
    {
        return; // If key already exists, do nothing
    }

    // Update the height of the current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Check the balance factor of the node
    int balance = getBalance(node);

    // Perform rotations if needed to balance the tree
    if (balance > 1 && key < node->left->key)
    {
        rightRotate(node); // Left-left case
    }
    else if (balance < -1 && key > node->right->key)
    {
        leftRotate(node); // Right-right case
    }
    else if (balance > 1 && key > node->left->key)
    {
        leftRotate(node->left); // Left-right case
        rightRotate(node);      // After left rotation, perform right rotation
    }
    else if (balance < -1 && key < node->right->key)
    {
        rightRotate(node->right); // Right-left case
        leftRotate(node);         // After right rotation, perform left rotation
    }
}

// Min value node function for deletion
void minValueNode(struct Node *node, struct Node *&minNode)
{
    struct Node *current = node;
    while (current->left != NULL)
    {
        current = current->left;
    }
    minNode = current;
}

// Delete function with balancing and rotation
void deleteNode(struct Node *&root, int key)
{
    if (root == NULL)
    {
        return;
    }

    if (key < root->key)
    {
        deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        deleteNode(root->right, key);
    }
    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            struct Node *temp = (root->left != NULL) ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
            }
            delete temp;
        }
        else
        {
            struct Node *temp;
            minValueNode(root->right, temp);
            root->key = temp->key;
            deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
    {
        return;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    // Perform rotations if needed to balance the tree
    if (balance > 1 && getBalance(root->left) >= 0)
    {
        rightRotate(root);
    }
    else if (balance > 1 && getBalance(root->left) < 0)
    {
        leftRotate(root->left);
        rightRotate(root);
    }
    else if (balance < -1 && getBalance(root->right) <= 0)
    {
        leftRotate(root);
    }
    else if (balance < -1 && getBalance(root->right) > 0)
    {
        rightRotate(root->right);
        leftRotate(root);
    }
}

// In-order traversal
void inOrder(struct Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

// Pre-order traversal
void preOrder(struct Node *root)
{
    if (root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Post-order traversal
void postOrder(struct Node *root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}

// Search function
void search(struct Node *root, int key)
{
    if (root == NULL)
    {
        cout << key << " not found!" << endl;
        return;
    }
    if (key == root->key)
    {
        cout << key << " found!" << endl;
        return;
    }
    if (key < root->key)
    {
        search(root->left, key);
    }
    else
    {
        search(root->right, key);
    }
}

// Main function with menu
int main()
{
    struct Node *root = NULL;
    int choice, value;

    while (true)
    {
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

        if (choice == 0)
        {
            break;
        }

        switch (choice)
        {
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
            cout << "In-order: ";
            inOrder(root);
            cout << endl;
            break;
        case 5:
            cout << "Pre-order: ";
            preOrder(root);
            cout << endl;
            break;
        case 6:
            cout << "Post-order: ";
            postOrder(root);
            cout << endl;
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }

    cout << "Program exited.\n";
    return 0;
}
