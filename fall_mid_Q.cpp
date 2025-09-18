#include<bits/stdc++.h>
using namespace std;
struct node{
    struct node*prev;
    int data;
    struct node*next;
};
void mridul(struct node*&head,int data){
    struct node*temp=new node();
    temp->prev=NULL;
    temp->data=data;
    temp->next=NULL;
    struct node*ptr=head;
    temp->prev=ptr;
    temp->next=ptr->next;
    ptr->next->prev=temp;
    ptr->next=temp;
}
void mridul_delete(struct node*&head){
    struct node*ptr=head;
    struct node*temp=ptr->next;
    ptr->next=ptr->next->next;
    ptr->next->prev=ptr;
    delete(temp);   
}
int main(){
    struct node*head=NULL;
    struct node*node_1=new node{NULL,7,NULL};
    struct node*node_2=new node{NULL,9,NULL};
    node_1->next=node_2;
    node_2->prev=node_1;
    head=node_1;
    mridul(head,11); 
    mridul_delete(head);
    return 0;
}