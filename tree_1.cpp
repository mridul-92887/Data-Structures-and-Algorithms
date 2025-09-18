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
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    display(q);
    cout << "Dequeued: " << dequeue(q) << endl;
    cout << "Queue after dequeue: ";
    display(q);
    cout << "Front element: " << peek(q) << endl;
    return 0;
}