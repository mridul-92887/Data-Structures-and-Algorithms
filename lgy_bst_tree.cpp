#include <iostream>
#include <queue>
#include <climits>
using namespace std;

// Node structure for BST
struct TreeNode {
    int data;
    TreeNode* left = NULL;
    TreeNode* right = NULL;
};

// Insert a node into the BST
void insert(TreeNode*& root, int data) {
    if (root == NULL) {
        root = new TreeNode(); 
        root->data = data;
        cout << "Node " << data << " inserted." << endl;
    }
    else if (data < root->data) {
        insert(root->left, data); 
    }
    else {
        insert(root->right, data); 
    }
}

// Search for a node in the BST
void search(TreeNode* root, int key) {
    if (root == NULL) {
        cout << "Node " << key << " not found in the tree." << endl;
        return;
    }
    if (root->data == key) {
        cout << "Node " << key << " found in the tree." << endl;
        return;
    }
    else if (key < root->data) {
        search(root->left, key);
    }
    else {
        search(root->right, key);
    }
}

// Find the height of the tree
int height(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (1 + max(leftHeight, rightHeight));
}

// Count the number of nodes in the tree
int countNodes(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    int leftCount = countNodes(root->left);
    int rightCount = countNodes(root->right);
    return (1 + leftCount + rightCount);
}

// Check if the tree is balanced (helper function)
bool isBalancedHelper(TreeNode* root) {
    if (root == NULL) {
        return true;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    bool isCurrentBalanced = (abs(leftHeight - rightHeight) <= 1);
    return (isCurrentBalanced && isBalancedHelper(root->left) && isBalancedHelper(root->right));
}

// Check if the tree is balanced (main function)
void isBalanced(TreeNode* root) {
    if (isBalancedHelper(root)) {
        cout << "The tree is balanced." << endl;
    }
    else {
        cout << "The tree is not balanced." << endl;
    }
}

// Find the minimum value in the tree
void findMin(TreeNode* root) {
    if (root == NULL) {
        cout << "Minimum value not found, tree is empty." << endl;
        return;
    }
    while (root->left != NULL) {
        root = root->left;
    }
    cout << "Minimum value: " << root->data << endl;
}

// Find the maximum value in the tree
void findMax(TreeNode* root) {
    if (root == NULL) {
        cout << "Maximum value not found, tree is empty." << endl;
        return;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    cout << "Maximum value: " << root->data << endl;
}

// Check if the tree is a valid BST (helper function)
bool isValidBSTHelper(TreeNode* root, int min = INT_MIN, int max = INT_MAX) {
    if (root == NULL) {
        return true;
    }
    if ((root->data <= min) || (root->data >= max)) {
        return false;
    }
    bool leftValid = isValidBSTHelper(root->left, min, root->data);
    bool rightValid = isValidBSTHelper(root->right, root->data, max);
    return (leftValid && rightValid);
}

// Check if the tree is a valid BST (main function)
void isValidBST(TreeNode* root) {
    if (isValidBSTHelper(root)) {
        cout << "The tree is a valid BST." << endl;
    }
    else {
        cout << "The tree is not a valid BST." << endl;
    }
}

// Level Order Traversal (BFS)
void levelOrderTraversal(TreeNode* root) {
    if (root == NULL) {
        cout << "Tree is empty. No level order traversal possible." << endl;
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    cout << "Level Order Traversal: ";
    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        cout << current->data << " ";
        if (current->left != NULL) {
            q.push(current->left);
        }
        if (current->right != NULL) {
            q.push(current->right);
        }
    }
    cout << endl;
}

// Mirror the tree
void mirror(TreeNode*& root) {
    if (root == NULL) {
        return;
    }
    swap(root->left, root->right);
    mirror(root->left);
    mirror(root->right);
    cout << "Tree mirrored." << endl;
}

// Find the Lowest Common Ancestor (LCA)
void lowestCommonAncestor(TreeNode* root, int p, int q) {
    if (root == NULL) {
        cout << "LCA not found." << endl;
        return;
    }
    if ((root->data > p) && (root->data > q)) {
        lowestCommonAncestor(root->left, p, q);
    }
    else if ((root->data < p) && (root->data < q)) {
        lowestCommonAncestor(root->right, p, q);
    }
    else {
        cout << "Lowest Common Ancestor: " << root->data << endl;
    }
}

// Inorder Traversal (Left, Root, Right)
void inorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

// Preorder Traversal (Root, Left, Right)
void preorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Postorder Traversal (Left, Right, Root)
void postorderTraversal(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}

// Main function with test cases
int main() {
    TreeNode* root = NULL;
    int choice, value, p, q;

    while (true) {
        cout << "\n1. Insert\n2. Search\n3. Height\n4. Count Nodes\n5. Is Balanced\n6. Find Min\n7. Find Max\n8. Is Valid BST\n9. Level Order Traversal\n10. Mirror Tree\n11. Lowest Common Ancestor\n12. Inorder Traversal\n13. Preorder Traversal\n14. Postorder Traversal\n15. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                insert(root, value);
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> value;
                search(root, value);
                break;
            case 3:
                cout << "Height of the tree: " << height(root) << endl;
                break;
            case 4:
                cout << "Number of nodes: " << countNodes(root) << endl;
                break;
            case 5:
                isBalanced(root);
                break;
            case 6:
                findMin(root);
                break;
            case 7:
                findMax(root);
                break;
            case 8:
                isValidBST(root);
                break;
            case 9:
                levelOrderTraversal(root);
                break;
            case 10:
                mirror(root);
                break;
            case 11:
                cout << "Enter two values to find LCA: ";
                cin >> p >> q;
                lowestCommonAncestor(root, p, q);
                break;
            case 12:
                cout << "Inorder Traversal: ";
                inorderTraversal(root);
                cout << endl;
                break;
            case 13:
                cout << "Preorder Traversal: ";
                preorderTraversal(root);
                cout << endl;
                break;
            case 14:
                cout << "Postorder Traversal: ";
                postorderTraversal(root);
                cout << endl;
                break;
            case 15:
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
    return 0;
}