#include<bits/stdc++.h>
using namespace std;
struct node{
    string id;
    string name;
    struct node* next;
}; 
void add(struct node*&head,string id,string name){
    struct node*newnode=new node();
    newnode->id=id;
    newnode->name=name;
    newnode->next=NULL;
    if(head==NULL){
        head=newnode;
    }else{
        struct node*ptr=head;
        while(ptr->next!=NULL){
            ptr=ptr->next;
        }
        ptr->next=newnode;
    }
}
void display(struct node*head){
    struct node* ptr=head;
    cout << left << setw(10) << "ID" << setw(10) << "NAME" << endl;
    cout << "____________________" << endl;
    while(ptr!=NULL){
        cout << left << setw(10) << ptr->id << setw(10) << ptr->name << endl;
        ptr=ptr->next;
    }
}
void insert_first(struct node*&head,string id,string name){
    struct node*newnode=new node();
    newnode->id=id;
    newnode->name=name;
    newnode->next=head;
    head=newnode;
}
void insert_last(struct node*&head,string id,string name){
    struct node*newnode=new node();
    newnode->id=id;
    newnode->name=name;
    newnode->next=NULL;
    struct node*ptr=head;
    while(ptr->next!=NULL){
        ptr=ptr->next;
    }
    ptr->next=newnode;
}
void delete_first(struct node*&head){
    struct node*temp=head;
    head=head->next;
    delete(temp);
}
void delete_last(struct node*&head){
    struct node* temp=head;
    while(temp->next->next!=NULL){
        temp=temp->next;
    }
    delete(temp->next);
    temp->next=NULL;
}
void insert_by_position(struct node*&head,string id,string name,int p){
    struct node*newnode=new node();
    newnode->id=id;
    newnode->name=name;
    newnode->next=NULL;
    if(p==1){
        newnode->next=head;
        head=newnode;
        return;
    }else{
        struct node*ptr=head;
        for(int i=1;i<p-1&&ptr!=NULL;i++){
            ptr=ptr->next;
        }
        newnode->next=ptr->next;
        ptr->next=newnode;
    }
}
void delete_by_position(struct node*&head,int p){
    struct node*temp=head;
    if(p==1){
        head=head->next;
        delete(temp);
    }else{
        struct node*ptr=head;
        for(int i=1;i<p-1&&ptr!=NULL;i++){
            ptr=ptr->next;
        }
        temp=ptr->next;
        ptr->next=temp->next;
        delete(temp);
    }
}
int main(){
    struct node*head=NULL;
    while(true){
        cout<<"1. Add student details "<<endl;
        cout<<"2. Display "<<endl;
        cout<<"3. Insert First"<<endl;
        cout<<"4. Insert Last"<<endl;
        cout<<"5. Delete First"<<endl;
        cout<<"6. Delete Last"<<endl;
        cout<<"7. Insert By Position"<<endl;
        cout<<"8. Delete By Position"<<endl;
        int choice;
        cout<<"Enter your choice = ";
        cin>>choice;
        switch(choice){
            case 1:{
                int n;
                cout<<"Enter the number of student = ";
                cin>>n;
                for(int i=0;i<n;i++){
                    string id,name;
                    cout<<"Enter ID : ";
                    cin>>id;
                    cout<<"Enter NAME : ";
                    cin>>name;
                    add(head,id,name);
                }
                break;
            }
            case 2:{
                display(head);
                break;
            }
            case 3:{
                string id,name;
                cout<<"Enter ID : ";
                cin>>id;
                cout<<"Enter NAME : ";
                cin>>name;
                insert_first(head,id,name);
                break;
            }
            case 4:{
                string id,name;
                cout<<"Enter ID : ";
                cin>>id;
                cout<<"Enter NAME : ";
                cin>>name;
                insert_last(head,id,name);
                break;
            }
            case 5:{
                delete_first(head);
                break;
            }
            case 6:{
                delete_last(head);
                break;
            }
            case 7:{
                string id,name;
                cout<<"Enter ID : ";
                cin>>id;
                cout<<"Enter NAME : ";
                cin>>name;
                int p;
                cout<<"Plz enter the position = ";
                cin>>p;
                insert_by_position(head,id,name,p);
                break;
            }
            case 8:{
                int p;
                cout<<"Plz enter the position = ";
                cin>>p;
                delete_by_position(head,p);
                break;
            }
        }
    }
    return 0;
}