#include<bits/stdc++.h>
using namespace std;

struct node{
    string id;
    float cgpa;
    string name;
    struct node* link;
};

// Add a new node to the end of the list
void add(struct node*& head, string id, float cgpa, string name) {
    struct node* newnode = new node();
    newnode->id = id;
    newnode->cgpa = cgpa;
    newnode->name = name;
    newnode->link = NULL;
    if (head == NULL) {
        head = newnode;
    } else {
        struct node* ptr = head;
        while (ptr->link != NULL) {
            ptr = ptr->link;
        }
        ptr->link = newnode;
    }
}

// Display all student records
void display(struct node* head) {
    struct node* ptr = head;
    cout << left << setw(10) << "ID" << setw(10) << "CGPA" << setw(10) << "NAME" << endl;
    cout << "_" << endl;
    while (ptr != NULL) {
        cout << left << setw(10) << ptr->id << setw(10) << ptr->cgpa << setw(10) << ptr->name << endl;
        ptr = ptr->link;
    }
}

// Count total number of students
int countStudents(struct node* head){
    int count = 0;
    struct node* ptr = head;
    while (ptr != NULL) {
        count++;
        ptr = ptr->link;
    }
    return count;
}

// Insert a new node at the beginning of the list
void insertFirst(struct node*& head, string id, float cgpa, string name) {
    struct node* newnode = new node();
    newnode->id = id;
    newnode->cgpa = cgpa;
    newnode->name = name;
    newnode->link = head;
    head = newnode;
}

// Insert a new node after a specific node by ID
void insertAfter(struct node* head, string afterId, string id, float cgpa, string name) {
    struct node* ptr = head;
    while(ptr != NULL){
        if (ptr->id == afterId) {
            struct node* newnode = new node();
            newnode->id = id;
            newnode->cgpa = cgpa;
            newnode->name = name;
            newnode->link = ptr->link;
            ptr->link = newnode;
            cout << "Student inserted successfully after ID " << afterId << "." << endl;
            return;
        }
        ptr = ptr->link;
    }
    cout << "Student with ID " << afterId << " not found." << endl;
}

// Calculate the sum of all CGPAs
float sumCGPA(struct node* head) {
    float sum = 0;
    struct node* ptr = head;
    while (ptr != NULL) {
        sum += ptr->cgpa;
        ptr = ptr->link;
    }
    return sum;
}

// Find the student with the highest CGPA
void findHighestCGPA(struct node* head) {
    if (head == NULL) {
        cout << "No records available." << endl;
        return;
    }
    struct node* ptr = head;
    struct node* highest = head;
    while (ptr != NULL) {
        if (ptr->cgpa > highest->cgpa) {
            highest = ptr;
        }
        ptr = ptr->link;
    }
    cout << "Highest CGPA: " << highest->cgpa << " (" << highest->name << ", ID: " << highest->id << ")" << endl;
}

// Find the student with the lowest CGPA
void findLowestCGPA(struct node* head) {
    if (head == NULL) {
        cout << "No records available." << endl;
        return;
    }
    struct node* ptr = head;
    struct node* lowest = head;
    while (ptr != NULL) {
        if (ptr->cgpa < lowest->cgpa) {
            lowest = ptr;
        }
        ptr = ptr->link;
    }
    cout << "Lowest CGPA: " << lowest->cgpa << " (" << lowest->name << ", ID: " << lowest->id << ")" << endl;
}

// Search for a specific student by ID
void searchStudent(struct node* head, string id) {
    struct node* ptr = head;
    while (ptr != NULL) {
        if (ptr->id == id) {
            cout << "Student Found: " << endl;
            cout << "ID: " << ptr->id << ", Name: " << ptr->name << ", CGPA: " << ptr->cgpa << endl;
            return;
        }
        ptr = ptr->link;
    }
    cout << "Student with ID " << id << " not found." << endl;
}

// Update student details by ID
void updateStudent(struct node* head, string id) {
    struct node* ptr = head;
    while (ptr != NULL) {
        if (ptr->id == id) {
            cout << "Enter new name: ";
            cin >> ptr->name;
            cout << "Enter new CGPA: ";
            cin >> ptr->cgpa;
            cout << "Record updated successfully!" << endl;
            return;
        }
        ptr = ptr->link;
    }
    cout << "Student with ID " << id << " not found." << endl;
}

// Delete a student record by ID
void deleteStudent(struct node*& head, string id) {
    if (head == NULL) {
        cout << "No records to delete." << endl;
        return;
    }
    if (head->id == id) {
        struct node* temp = head;
        head = head->link;
        delete temp;
        cout << "Record deleted successfully!" << endl;
        return;
    }
    struct node* ptr = head;
    while (ptr->link != NULL && ptr->link->id != id) {
        ptr = ptr->link;
    }
    if (ptr->link == NULL) {
        cout << "Student with ID " << id << " not found." << endl;
    } else {
        struct node* temp = ptr->link;
        ptr->link = temp->link;
        delete temp;
        cout << "Record deleted successfully!" << endl;
    }
}

// Delete a node by its position (node number)
void deleteNodeByPosition(struct node*& head, int position) {
    if (head == NULL) {
        cout << "No records to delete." << endl;
        return;
    }
    if (position == 1) {
        struct node* temp = head;
        head = head->link;
        delete temp;
        cout << "Node at position " << position << " deleted successfully!" << endl;
        return;
    }
    struct node* ptr = head;
    for (int i = 1; i < position - 1 && ptr != NULL; i++) {
        ptr = ptr->link;
    }
    if (ptr == NULL || ptr->link == NULL) {
        cout << "Position " << position << " is out of range." << endl;
    } else {
        struct node* temp = ptr->link;
        ptr->link = temp->link;
        delete temp;
        cout << "Node at position " << position << " deleted successfully!" << endl;
    }
}

// Delete all student records
void deleteAllStudents(struct node*& head) {
    while (head != NULL) {
        struct node* temp = head;
        head = head->link;
        delete temp;
    }
    cout << "All student records have been deleted." << endl;
}
void count(struct node* head){
    struct node* ptr=head;
    int count=0;
    while(ptr!=NULL){
        count++;
        ptr=ptr->link;
    }
    cout<<" Total node = "<<count<<endl;
}
void delete_fast(struct node*& head){
    struct node* temp=head;
    head=head->link;
    delete(temp);
    cout<<"successful....."<<endl;
}
void delete_last(struct node*& head){
    struct node* temp=head;
    while(temp->link!=NULL){
        temp=temp->link;
    }
    delete(temp);
    cout<<"successful....."<<endl;
}
void reverse_list(struct node*& head){
    struct node* previous=NULL;
    struct node* current=head;
    struct node* next=NULL;
    while(current!=NULL){
        next=current->link;
        current->link=previous;
        previous=current;
        current=next;
    }
    head=previous;
}
void remove_duplicateIDdetails(struct node*& head) {
    struct node* ptr = head;
    while (ptr != NULL) {
        struct node* temp = ptr;
        while (temp->link != NULL && temp->link->id == ptr->id) {
            struct node* duplicate = temp->link;
            temp->link = temp->link->link;
            delete duplicate;
        }
        ptr = ptr->link;
    }
}

int main() {
    struct node* head = NULL;
    while (true) {
        cout << "\nMENU_" << endl;
        cout << "1. Display" << endl;
        cout << "2. Total Student" << endl;
        cout << "3. Add Multiple Students" << endl;
        cout << "4. Insert First" << endl;
        cout << "5. Insert Last" << endl;
        cout << "6. Insert After a Node" << endl;
        cout << "7. Sum of all CGPAs" << endl;
        cout << "8. Search Specific Student" << endl;
        cout << "9. Highest CGPA" << endl;
        cout << "10. Lowest CGPA" << endl;
        cout << "11. Update Student Details" << endl;
        cout << "12. Delete a Student Data" << endl;
        cout << "13. Delete All Students" << endl;
        cout << "14. Delete Node by Position" << endl;
        cout << "15. Delete Fast node" << endl;
        cout << "16. Delete Last node" << endl;
        cout << "17. Count total node" << endl;
        cout << "18. Reverse list" <<endl;
        cout << "19. Delete duplicate node" <<endl;
        cout << "20. Exit....." << endl;
        
        int choice;
        cout << "\nEnter Your Choice = ";
        cin >> choice;

        switch (choice) {
            case 1:
                display(head);
                break;
            case 2:
                cout << "Total Students: " << countStudents(head) << endl;
                break;
            case 3: {
                int n;
                cout << "How many students do you want to add? ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    string id, name;
                    float cgpa;
                    cout << "Enter ID: ";
                    cin >> id;
                    cout << "Enter CGPA: ";
                    cin >> cgpa;
                    cout << "Enter Name: ";
                    cin >> name;
                    add(head, id, cgpa, name);
                }
                break;
            }
            case 4: {
                string id, name;
                float cgpa;
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter CGPA: ";
                cin >> cgpa;
                cout << "Enter Name: ";
                cin >> name;
                insertFirst(head, id, cgpa, name);
                break;
            }
            case 5: {
                string id, name;
                float cgpa;
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter CGPA: ";
                cin >> cgpa;
                cout << "Enter Name: ";
                cin >> name;
                add(head, id, cgpa, name);
                break;
            }
            case 6: {
                string afterId, id, name;
                float cgpa;
                cout << "Enter the ID of the student after which to insert: ";
                cin >> afterId;
                cout << "Enter new ID: ";
                cin >> id;
                cout << "Enter new CGPA: ";
                cin >> cgpa;
                cout << "Enter new Name: ";
                cin >> name;
                insertAfter(head, afterId, id, cgpa, name);
                break;
            }
            case 7:
                cout << "Sum of all CGPAs: " << sumCGPA(head) << endl;
                break;
            case 8: {
                string id;
                cout << "Enter ID to search: ";
                cin >> id;
                searchStudent(head, id);
                break;
            }
            case 9:
                findHighestCGPA(head);
                break;
            case 10:
                findLowestCGPA(head);
                break;
            case 11: {
                string id;
                cout << "Enter ID to update: ";
                cin >> id;
                
                updateStudent(head, id);
                break;
            }
            case 12: {
                string id;
                cout << "Enter ID to delete: ";
                cin >> id;
                deleteStudent(head, id);
                break;
            }
            case 13:
                deleteAllStudents(head);
                break;
            case 14: {
                int position;
                cout << "Enter the position of the node to delete: ";
                cin >> position;
                deleteNodeByPosition(head, position);
                break;
            }
            case 15: {
                delete_fast(head);
                break;
            }
            case 16:
                delete_last(head);
                break;
            case 17:
                count(head);
            break;
            case 18:
                reverse_list(head);
                break;
            case 19:
                remove_duplicateIDdetails(head);
                break;
            case 20:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}