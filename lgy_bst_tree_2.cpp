#include<bits/stdc++.h>
using namespace std;

struct tree {
    int data;
    struct tree* left = NULL;
    struct tree* right = NULL;  
};

// Insert a new node in BST
void insert(struct tree*& root, int data) {
    if(root == NULL) {
        root = new tree();
        root->data = data;
    }
    else if(data < root->data) {
        insert(root->left, data);
    }
    else {
        insert(root->right, data);
    }
}

// Search for a value in BST
void search(struct tree* root, int data) {
    if(root == NULL) {
        cout << "Value " << data << " not found in tree." << endl;
        return;
    }
    if(root->data == data) {
        cout << "Value " << data << " found in tree!" << endl;
        return;
    }
    else if(data < root->data) {
        search(root->left, data);
    }
    else {
        search(root->right, data);
    }
}

// Calculate height of the tree
int height(struct tree* root) {
    if(root == NULL) {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

// Count total nodes in the tree
int countNodes(struct tree* root) {
    if(root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Find and display minimum value
void findMin(struct tree* root) {
    if(root == NULL) {
        cout << "Tree is empty!" << endl;
        return;
    }
    while(root->left != NULL) {
        root = root->left;
    }
    cout << "Minimum value in tree: " << root->data << endl;
}

// Find and display maximum value
void findMax(struct tree* root) {
    if(root == NULL) {
        cout << "Tree is empty!" << endl;
        return;
    }
    while(root->right != NULL) {
        root = root->right;
    }
    cout << "Maximum value in tree: " << root->data << endl;
}

// Tree traversals
void preorderTraversal(struct tree* root) {
    if(root == NULL) return;
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void inorderTraversal(struct tree* root) {
    if(root == NULL) return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

void postorderTraversal(struct tree* root) {
    if(root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}

// Check if tree is balanced
bool isBalancedHelper(struct tree* root) {
    if(root == NULL) return true;
    int diff = abs(height(root->left) - height(root->right));
    return (diff <= 1) && isBalancedHelper(root->left) && isBalancedHelper(root->right);
}

void isBalanced(struct tree* root) {
    if(isBalancedHelper(root)) {
        cout << "Tree is balanced." << endl;
    }
    else {
        cout << "Tree is not balanced." << endl;
    }
}

// Delete a node from BST
struct tree* findMinNode(struct tree* node) {
    while(node->left != NULL) {
        node = node->left;
    }
    return node;
}
void deleteNode(struct tree*& root, int data) {
    if(root == NULL) return;

    if(data < root->data) {
        deleteNode(root->left, data);
    }
    else if(data > root->data) {
        deleteNode(root->right, data);
    }
    else {
        // Node with only one child or no child
        if(root->left == NULL) {
            struct tree* temp = root;
            root = root->right;
            delete temp;
        }
        else if(root->right == NULL) {
            struct tree* temp = root;
            root = root->left;
            delete temp;
        }
        else {
            // Node with two children
            struct tree* temp = findMinNode(root->right);
            root->data = temp->data;
            deleteNode(root->right, temp->data);  // delete the inorder successor
        }
    }
}


// Level order traversal
void levelOrderTraversal(struct tree* root) {
    if(root == NULL) {
        cout << "Tree is empty!" << endl;
        return;
    }
    
    queue<tree*> q;
    q.push(root);
    
    cout << "Level Order Traversal: ";
    while(!q.empty()) {
        tree* current = q.front();
        q.pop();
        cout << current->data << " ";
        
        if(current->left) q.push(current->left);
        if(current->right) q.push(current->right);
    }
    cout << endl;
}

// Find successor (next larger value)
void findSuccessor(struct tree* root, int val) {
    struct tree* successor = NULL;
    while(root) {
        if(val < root->data) {
            successor = root;
            root = root->left;
        }
        else if(val > root->data) {
            root = root->right;
        }
        else {
            if(root->right) {
                root = root->right;
                while(root->left) root = root->left;
                successor = root;
            }
            break;
        }
    }
    
    if(successor) {
        cout << "Successor of " << val << " is: " << successor->data << endl;
    }
    else {
        cout << "No successor found for " << val << endl;
    }
}

// Find predecessor (previous smaller value)
void findPredecessor(struct tree* root, int val) {
    struct tree* predecessor = NULL;
    while(root) {
        if(val < root->data) {
            root = root->left;
        }
        else if(val > root->data) {
            predecessor = root;
            root = root->right;
        }
        else {
            if(root->left) {
                root = root->left;
                while(root->right) root = root->right;
                predecessor = root;
            }
            break;
        }
    }
    
    if(predecessor) {
        cout << "Predecessor of " << val << " is: " << predecessor->data << endl;
    }
    else {
        cout << "No predecessor found for " << val << endl;
    }
}

// Display menu options
void displayMenu() {
    cout << "\n========== BST Operations Menu ==========" << endl;
    cout << "1. Insert a new value" << endl;
    cout << "2. Search for a value" << endl;
    cout << "3. Get tree height" << endl;
    cout << "4. Count nodes in tree" << endl;
    cout << "5. Find minimum value" << endl;
    cout << "6. Find maximum value" << endl;
    cout << "7. Preorder traversal" << endl;
    cout << "8. Inorder traversal" << endl;
    cout << "9. Postorder traversal" << endl;
    cout << "10. Check if tree is balanced" << endl;
    cout << "11. Delete a value" << endl;
    cout << "12. Level order traversal" << endl;
    cout << "13. Find successor" << endl;
    cout << "14. Find predecessor" << endl;
    cout << "15. Exit program" << endl;
    cout << "=======================================" << endl;
    cout << "Enter your choice (1-15): ";
}

int main() {
    struct tree* root = NULL;
    int choice, value;
    
    while(true) {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                insert(root, value);
                cout << "Value " << value << " inserted successfully." << endl;
                break;
                
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                search(root, value);
                break;
                
            case 3:
                cout << "Tree height: " << height(root) << endl;
                break;
                
            case 4:
                cout << "Total nodes in tree: " << countNodes(root) << endl;
                break;
                
            case 5:
                findMin(root);
                break;
                
            case 6:
                findMax(root);
                break;
                
            case 7:
                cout << "Preorder Traversal: ";
                preorderTraversal(root);
                cout << endl;
                break;
                
            case 8:
                cout << "Inorder Traversal: ";
                inorderTraversal(root);
                cout << endl;
                break;
                
            case 9:
                cout << "Postorder Traversal: ";
                postorderTraversal(root);
                cout << endl;
                break;
                
            case 10:
                isBalanced(root);
                break;
                
            case 11:
                cout << "Enter value to delete: ";
                cin >> value;
                deleteNode(root, value);
                cout << "Value " << value << " deleted successfully." << endl;
                break;
                
            case 12:
                levelOrderTraversal(root);
                break;
                
            case 13:
                cout << "Enter value to find successor: ";
                cin >> value;
                findSuccessor(root, value);
                break;
                
            case 14:
                cout << "Enter value to find predecessor: ";
                cin >> value;
                findPredecessor(root, value);
                break;
                
            case 15:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
                
            default:
                cout << "Invalid choice! Please enter a number between 1-15." << endl;
        }
    }
    
    return 0;
}