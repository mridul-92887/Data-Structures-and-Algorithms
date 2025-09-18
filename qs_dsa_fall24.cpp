#include <bits/stdc++.h>
using namespace std;

struct CandidateNode {
    int id;
    struct CandidateNode* left = NULL;
    struct CandidateNode* right = NULL;
};

// Insert a new candidate ID into the BST
void insertCandidate(struct CandidateNode*& root, int id) {
    if(root == NULL) {
        root = new CandidateNode();
        root->id = id;
    }
    else if(id < root->id) {
        insertCandidate(root->left, id);
    }
    else {
        insertCandidate(root->right, id);
    }
}

// Search for a candidate by ID
void searchCandidate(struct CandidateNode* root, int id) {
    if(root == NULL) {
        cout << "Candidate with ID " << id << " not found in system." << endl;
        return;
    }
    if(root->id == id) {
        cout << "Candidate with ID " << id << " found in system!" << endl;
        return;
    }
    else if(id < root->id) {
        searchCandidate(root->left, id);
    }
    else {
        searchCandidate(root->right, id);
    }
}

// Display all candidate IDs in in-order traversal
void displayCandidates(struct CandidateNode* root) {
    if(root == NULL) return;
    displayCandidates(root->left);
    cout << root->id << " ";
    displayCandidates(root->right);
}

// Count total candidates in the system
int countCandidates(struct CandidateNode* root) {
    if(root == NULL) {
        return 0;
    }
    return 1 + countCandidates(root->left) + countCandidates(root->right);
}

// Find and display minimum candidate ID
void findMinID(struct CandidateNode* root) {
    if(root == NULL) {
        cout << "No candidates in system!" << endl;
        return;
    }
    while(root->left != NULL) {
        root = root->left;
    }
    cout << "Minimum candidate ID: " << root->id << endl;
}

// Find and display maximum candidate ID
void findMaxID(struct CandidateNode* root) {
    if(root == NULL) {
        cout << "No candidates in system!" << endl;
        return;
    }
    while(root->right != NULL) {
        root = root->right;
    }
    cout << "Maximum candidate ID: " << root->id << endl;
}

// Delete a candidate from the system
struct CandidateNode* findMinNode(struct CandidateNode* node) {
    while(node->left != NULL) {
        node = node->left;
    }
    return node;
}

struct CandidateNode* deleteCandidate(struct CandidateNode* root, int id) {
    if(root == NULL) return root;
    
    if(id < root->id) {
        root->left = deleteCandidate(root->left, id);
    }
    else if(id > root->id) {
        root->right = deleteCandidate(root->right, id);
    }
    else {
        // Node with only one child or no child
        if(root->left == NULL) {
            struct CandidateNode* temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == NULL) {
            struct CandidateNode* temp = root->left;
            delete root;
            return temp;
        }
        
        // Node with two children
        struct CandidateNode* temp = findMinNode(root->right);
        root->id = temp->id;
        root->right = deleteCandidate(root->right, temp->id);
    }
    return root;
}

// Display menu options
void displayMenu() {
    cout << "\n========== Election Commission System ==========" << endl;
    cout << "1. Insert a new candidate ID" << endl;
    cout << "2. Search for a candidate by ID" << endl;
    cout << "3. Display all candidate IDs (in-order)" << endl;
    cout << "4. Count total candidates" << endl;
    cout << "5. Find minimum candidate ID" << endl;
    cout << "6. Find maximum candidate ID" << endl;
    cout << "7. Delete a candidate by ID" << endl;
    cout << "8. Exit program" << endl;
    cout << "==============================================" << endl;
    cout << "Enter your choice (1-8): ";
}

int main() {
    struct CandidateNode* root = NULL;
    int choice, id;
    
    while(true) {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                cout << "Enter candidate ID to insert: ";
                cin >> id;
                insertCandidate(root, id);
                cout << "Candidate ID " << id << " inserted successfully." << endl;
                break;
                
            case 2:
                cout << "Enter candidate ID to search: ";
                cin >> id;
                searchCandidate(root, id);
                break;
                
            case 3:
                cout << "All candidate IDs (in-order): ";
                displayCandidates(root);
                cout << endl;
                break;
                
            case 4:
                cout << "Total candidates in system: " << countCandidates(root) << endl;
                break;
                
            case 5:
                findMinID(root);
                break;
                
            case 6:
                findMaxID(root);
                break;
                
            case 7:
                cout << "Enter candidate ID to delete: ";
                cin >> id;
                root = deleteCandidate(root, id);
                cout << "Candidate ID " << id << " deleted successfully." << endl;
                break;
                
            case 8:
                cout << "Exiting Election Commission System. Goodbye!" << endl;
                return 0;
                
            default:
                cout << "Invalid choice! Please enter a number between 1-8." << endl;
        }
    }
    
    return 0;
}