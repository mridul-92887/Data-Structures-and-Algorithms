#include <iostream>
using namespace std;

struct node {
    int data = 0;
    struct node* next = NULL;
};

struct Queue {
    struct node* front = NULL;
    struct node* rear = NULL;
};

void enqueue(Queue& q, int value) {
    struct node* newNode = new node();
    newNode->data = value;
    newNode->next = NULL;

    if (q.rear == NULL) {
        q.front = q.rear = newNode;
    } else {
        q.rear->next = newNode;
        q.rear = newNode;
    }
}

int dequeue(Queue& q) {
    if (q.front == NULL) {
        cout << "Queue is empty!" << endl;
        return -1;
    }

    struct node* temp = q.front;
    int dequeuedValue = q.front->data;
    q.front = q.front->next;

    if (q.front == NULL) {
        q.rear = NULL;
    }

    delete temp;
    return dequeuedValue;
}

int peek(const Queue& q) {
    if (q.front == NULL) {
        cout << "Queue is empty!" << endl;
        return -1;
    }
    return q.front->data;
}

void display(const Queue& q) {
    if (q.front == NULL) {
        cout << "Queue is empty!" << endl;
        return;
    }

    struct node* temp = q.front;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    Queue q;
    int choice, value;

    while (true) {
        cout << "\n1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> value;
                enqueue(q, value);
                break;
            case 2:
                value = dequeue(q);
                if (value != -1) {
                    cout << "Dequeued: " << value << endl;
                }
                break;
            case 3:
                value = peek(q);
                if (value != -1) {
                    cout << "Front element: " << value << endl;
                }
                break;
            case 4:
                cout << "Queue: ";
                display(q);
                break;
            case 5:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}