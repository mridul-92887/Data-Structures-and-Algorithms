#include <bits/stdc++.h>
using namespace std;
struct node
{
    int data;
    struct node *next;
};
void add_end(struct node *&head, int data)
{
    struct node *newnode = new node();
    newnode->data = data;
    newnode->next = NULL;
    if (head == NULL)
    {
        head = newnode;
    }
    else
    {
        struct node *ptr = head;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = newnode;
    }
}
void join_2_list(struct node *list_1, struct node *list_2, struct node *&list_3)
{
    struct node *ptr = list_1;
    while (ptr != NULL)
    {
        add_end(list_3, ptr->data);
        ptr = ptr->next;
    }
    ptr = list_2;
    while (ptr != NULL)
    {
        add_end(list_3, ptr->data);
        ptr = ptr->next;
    }
}
void printList(struct node *head)
{
    struct node *ptr = head;
    while (ptr != NULL)
    {
        cout << ptr->data << " -> ";
        ptr = ptr->next;
    }
    cout << "NULL" << endl;
}
int main()
{
    struct node *list_1 = NULL;
    add_end(list_1, 100);
    add_end(list_1, 200);

    struct node *list_2 = NULL;
    add_end(list_2, 300);
    add_end(list_2, 400);

    struct node *list_3 = NULL;
    join_2_list(list_1, list_2, list_3);
    printList(list_3);
    return 0;
}