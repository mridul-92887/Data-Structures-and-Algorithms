#include<bits/stdc++.h>
using namespace std;

struct node {
    string id;
    float cgpa;
    string name;
    struct node* prev;
    struct node* next;
};

// Add a new node to the end of the list
void add(struct node*& head, string id, float cgpa, string name) {
    struct node* newnode = new node();
    newnode->id = id;
    newnode->cgpa = cgpa;
    newnode->name = name;
    newnode->prev = NULL;
    newnode->next = NULL;

    if (head == NULL) {
        head = newnode;
    } else {
        struct node* ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = newnode;
        newnode->prev = ptr;
    }
}

// Display all student records
void display(struct node* head) {
    struct node* ptr = head;
    cout << left << setw(10) << "ID" << setw(10) << "CGPA" << setw(10) << "NAME" << endl;
    cout << "_________________________________________" << endl;
    while (ptr != NULL) {
        cout << left << setw(10) << ptr->id << setw(10) << ptr->cgpa << setw(10) << ptr->name << endl;
        ptr = ptr->next;
    }
}

// Display the list in reverse order
void displayReverse(struct node* head) {
    if (head == NULL) return;

    struct node* ptr = head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }

    cout << left << setw(10) << "ID" << setw(10) << "CGPA" << setw(10) << "NAME" << endl;
    cout << "_________________________________________" << endl;
    while (ptr != NULL) {
        cout << left << setw(10) << ptr->id << setw(10) << ptr->cgpa << setw(10) << ptr->name << endl;
        ptr = ptr->prev;
    }
}

// Count total number of students
int countStudents(struct node* head) {
    int count = 0;
    struct node* ptr = head;
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }
    return count;
}

// Insert a new node at the beginning of the list
void insertFirst(struct node*& head, string id, float cgpa, string name) {
    struct node* newnode = new node();
    newnode->id = id;
    newnode->cgpa = cgpa;
    newnode->name = name;
    newnode->prev = NULL;
    newnode->next = head;

    if (head != NULL) {
        head->prev = newnode;
    }
    head = newnode;
}

// Insert a new node after a specific node by ID
void insertAfter(struct node* head, string afterId, string id, float cgpa, string name) {
    struct node* ptr = head;
    while (ptr != NULL) {
        if (ptr->id == afterId) {
            struct node* newnode = new node();
            newnode->id = id;
            newnode->cgpa = cgpa;
            newnode->name = name;
            newnode->prev = ptr;
            newnode->next = ptr->next;

            if (ptr->next != NULL) {
                ptr->next->prev = newnode;
            }
            ptr->next = newnode;
            cout << "Student inserted successfully after ID " << afterId << "." << endl;
            return;
        }
        ptr = ptr->next;
    }
    cout << "Student with ID " << afterId << " not found." << endl;
}

// Calculate the sum of all CGPAs
float sumCGPA(struct node* head) {
    float sum = 0;
    struct node* ptr = head;
    while (ptr != NULL) {
        sum += ptr->cgpa;
        ptr = ptr->next;
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
        ptr = ptr->next;
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
        ptr = ptr->next;
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
        ptr = ptr->next;
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
        ptr = ptr->next;
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
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        delete temp;
        cout << "Record deleted successfully!" << endl;
        return;
    }
    struct node* ptr = head;
    while (ptr->next != NULL && ptr->next->id != id) {
        ptr = ptr->next;
    }
    if (ptr->next == NULL) {
        cout << "Student with ID " << id << " not found." << endl;
    } else {
        struct node* temp = ptr->next;
        ptr->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = ptr;
        }
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
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        }
        delete temp;
        cout << "Node at position " << position << " deleted successfully!" << endl;
        return;
    }
    struct node* ptr = head;
    for (int i = 1; i < position - 1 && ptr != NULL; i++) {
        ptr = ptr->next;
    }
    if (ptr == NULL || ptr->next == NULL) {
        cout << "Position " << position << " is out of range." << endl;
    } else {
        struct node* temp = ptr->next;
        ptr->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = ptr;
        }
        delete temp;
        cout << "Node at position " << position << " deleted successfully!" << endl;
    }
}

// Delete all student records
void deleteAllStudents(struct node*& head) {
    while (head != NULL) {
        struct node* temp = head;
        head = head->next;
        delete temp;
    }
    cout << "All student records have been deleted." << endl;
}

// Count total nodes
void count(struct node* head) {
    struct node* ptr = head;
    int count = 0;
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }
    cout << "Total nodes = " << count << endl;
}

// Delete the first node
void delete_fast(struct node*& head) {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }
    struct node* temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    delete temp;
    cout << "First node deleted successfully!" << endl;
}

// Delete the last node
void delete_last(struct node*& head) {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }
    struct node* ptr = head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    if (ptr->prev != NULL) {
        ptr->prev->next = NULL;
    } else {
        head = NULL;
    }
    delete ptr;
    cout << "Last node deleted successfully!" << endl;
}

// Reverse the list
void reverse_list(struct node*& head) {
    struct node* temp = NULL;
    struct node* current = head;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL) {
        head = temp->prev;
    }
}

// Remove duplicate nodes by ID
void remove_duplicateIDdetails(struct node*& head) {
    struct node* ptr = head;
    while (ptr != NULL) {
        struct node* temp = ptr->next;
        while (temp != NULL) {
            if (temp->id == ptr->id) {
                struct node* duplicate = temp;
                if (temp->prev != NULL) {
                    temp->prev->next = temp->next;
                }
                if (temp->next != NULL) {
                    temp->next->prev = temp->prev;
                }
                temp = temp->next;
                delete duplicate;
            } else {
                temp = temp->next;
            }
        }
        ptr = ptr->next;
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
        cout << "15. Delete First node" << endl;
        cout << "16. Delete Last node" << endl;
        cout << "17. Count total node" << endl;
        cout << "18. Reverse list" << endl;
        cout << "19. Delete duplicate node" << endl;
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
            case 15:
                delete_fast(head);
                break;
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