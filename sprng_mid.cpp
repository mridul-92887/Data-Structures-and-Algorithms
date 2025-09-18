#include <bits/stdc++.h>
using namespace std;
struct node {
    string name;
    struct node* next;
};
void insertEnd(struct node*& head, string name) {
    struct node* newNode = new node{name, NULL};
    if (head == NULL) {
        head = newNode;
    } else {
        struct node* ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }
}
void joinLists(struct node* lst1, struct node* lst2, struct node*& lst3) {
    struct node* ptr = lst1;
    while (ptr != NULL) {
        insertEnd(lst3, ptr->name);
        ptr = ptr->next;
    }
    ptr = lst2;
    while (ptr != NULL) {
        insertEnd(lst3, ptr->name);
        ptr = ptr->next;
    }
}
void printList(struct node* head) {
    struct node* ptr = head;
    while (ptr != NULL) {
        cout << ptr->name << " -> ";
        ptr = ptr->next;
    }
    cout << "NULL" << endl;
}

void deleteList(struct node*& head) {
    while (head != NULL) {
        struct node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    struct node* lst1 = NULL;
    insertEnd(lst1, "Alice");
    insertEnd(lst1, "Bob");
    insertEnd(lst1, "Charlie");
    insertEnd(lst1, "David");
    insertEnd(lst1, "Eve");

    struct node* lst2 = NULL;
    insertEnd(lst2, "Frank");
    insertEnd(lst2, "Grace");
    insertEnd(lst2, "Hank");
    insertEnd(lst2, "Ivy");
    insertEnd(lst2, "Jack");

    struct node* lst3 = NULL;

    joinLists(lst1, lst2, lst3);

    cout << "lst1: ";
    printList(lst1);

    cout << "lst2: ";
    printList(lst2);

    cout << "lst3: ";
    printList(lst3);
    return 0;
}