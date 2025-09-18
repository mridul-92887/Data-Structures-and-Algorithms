#include<bits/stdc++.h>
using namespace std;
struct tree{
    int data;
    struct tree* left=NULL;
    struct tree* right=NULL;  
};
void insert(struct tree*& root,int data){
    if(root==NULL){
        root= new tree();
        root->data=data;
    }else if(data<root->data){
        insert(root->left,data);
    }else{
        insert(root->right,data);
    }
}
void search(struct tree* root, int data){
    if(root==NULL){
        return;
    }
    if(root->data==data){
        cout<<"Found"<<endl;
        return;
    }
    else if (data<root->data) {
        search(root->left,data);
    }
    else {
        search(root->right,data);
    }
}
int height(struct tree* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (1 + max(leftHeight, rightHeight));
}
int countNodes(struct tree* root) {
    if (root == NULL) {
        return 0;
    }
    int leftCount = countNodes(root->left);
    int rightCount = countNodes(root->right);
    return (1 + leftCount + rightCount);
}
void findMin(struct tree* root) {
    if (root == NULL) {
        cout << "Minimum value not found, tree is empty." << endl;
        return;
    }
    while(root->left != NULL){
        root = root->left;
    }
    cout << "Minimum value: " << root->data << endl;
}
void findMax(struct tree* root) {
    if (root == NULL) {
        cout << "Maximum value not found, tree is empty." << endl;
        return;
    }
    while (root->right != NULL) {
        root = root->right;
    }
    cout << "Maximum value: " << root->data << endl;
}
void preorderTraversal(struct tree* root) {
    if (root == NULL) {
        return;
    }
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}
void inorderTraversal(struct tree* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}
void postorderTraversal(struct tree* root) {
    if (root == NULL) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";

}
bool isBalancedHelper(struct tree*root){
    if(root==NULL){
        return true;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    bool isCurrentBalanced = (abs(leftHeight - rightHeight) <= 1);
    return (isCurrentBalanced && isBalancedHelper(root->left) && isBalancedHelper(root->right));
}
void isBalanced(struct tree* root) {
    if (isBalancedHelper(root)) {
        cout << "The tree is balanced." << endl;
    }
    else {
        cout << "The tree is not balanced." << endl;
    }
}

struct tree* findMinNode(struct tree* node) {
    while(node->left != NULL) {
        node = node->left;
    }
    return node;
}
struct tree* deleteNode(struct tree* root, int data) {
    if(root == NULL){
        return root;
    }else if(data<root->data){
        root->left=deleteNode(root->left,data);
    }
    else if(data>root->data){
        root->right=deleteNode(root->right,data);
    }
    else{
        if(root->left==NULL&&root->right==NULL){
            delete root;
            root = NULL;
        }
        else if(root->left==NULL){
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
            struct tree* temp = findMinNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}
void levelOrderTraversal(struct tree* root) {
    if(root == NULL) {
        cout << "Tree is empty." << endl;
        return;
    }
    queue<tree*> q;
    q.push(root);
    cout << "Level Order Traversal: ";
    while(!q.empty()) {
        tree* current = q.front();
        q.pop();
        cout << current->data << " ";
        
        if(current->left != NULL)
            q.push(current->left);
        if(current->right != NULL)
            q.push(current->right);
    }
    cout << endl;
}
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
    
    if(successor) 
        cout << "Successor: " << successor->data << endl;
    else
        cout << "No successor found" << endl;
}
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
    
    if(predecessor)
        cout << "Predecessor: " << predecessor->data << endl;
    else
        cout << "No predecessor found" << endl;
}

int main(){
    struct tree* root=NULL;
    while(true){
        cout<<"1.Insert"<<endl;
        cout<<"2.Search"<<endl;
        cout<<"3.Height"<<endl;
        cout<<"4.Count"<<endl;
        cout<<"5.Find MIN"<<endl;
        cout<<"6.Find MAX"<<endl;
        cout<<"7.Preorder"<<endl;
        cout<<"8.Inorder"<<endl;
        cout<<"9.Postorder"<<endl;
        cout<<"10.Balance Check"<<endl;
        cout<<"11.Delete data"<<endl;
        cout<<"12.Level Order Traversal"<<endl;
        cout<<"13.Find Successor"<<endl;
        cout<<"14.Find Predecessor"<<endl;
        int c;
        cout<<"enter = ";
        cin>>c;
        switch(c){
            case 1:{
                int data;
                cin>>data;
                insert(root,data);
                break;
            }
            case 2:{
                int data;
                cin>>data;
                search(root,data);
                break;
            }
            case 3:{
                cout<<height(root)<<endl;
                break;
            }
            case 4:{
                cout<<countNodes(root)<<endl;
                break;
            }
            case 5:{
                findMin(root);
                break;
            }
            case 6:{
                findMax(root);
                break;
            }
            case 7:{
                preorderTraversal(root);
                cout << endl;
                break;
            }
            case 8:{
                inorderTraversal(root);
                cout << endl;
                break;
            }
            case 9:{
                postorderTraversal(root);
                cout << endl;
                break;
            }
            case 10:{
                isBalanced(root);
                break;
            }
            case 11:{
                int data;
                cout << "Enter value to delete: ";
                cin >> data;
                root = deleteNode(root, data);
                break;
            }
            case 12:{
                levelOrderTraversal(root);
                break;
            }
            case 13: {
                int val;
                cout << "Enter value to find successor: ";
                cin >> val;
                findSuccessor(root, val);
                break;
            }
            case 14: {
                int val;
                cout << "Enter value to find predecessor: ";
                cin >> val;
                findPredecessor(root, val);
                break;
            }
            default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
    return 0;
}