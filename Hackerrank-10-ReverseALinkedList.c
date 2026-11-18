#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node *next;
};
struct Node* val_in_linked_list(struct Node* head){
    int num;
    struct Node *temp=NULL,*newnode=NULL;
    printf("Enter no of nodes:");
    scanf("%d",&num);
    for(int i=0;i<num;i++){
       newnode=malloc(sizeof(struct Node));
       scanf("%d",&newnode->data);
       newnode->next=NULL;
       if(head==NULL){
        head=newnode;
        temp=newnode;
       }
       else{
        temp->next=newnode;
        temp=newnode;
       }
    }
    return head;
}

struct Node* reverse(struct Node* llist) {
struct Node *curr=llist;
struct Node *prev=NULL;
struct Node *next=NULL;
while(curr!=NULL){
    next=curr->next;
    curr->next=prev;
    prev=curr;
    curr=next;
}
return prev;
}
void printing(struct Node *head){
    while(head!=NULL){
        printf("%d->",head->data);
        head=head->next;
    }
    printf("NULL\n");
}

int main(){
    int no_of_linked_list;
    printf("Enter No of Linked List Need to be reversed:");
    scanf("%d",&no_of_linked_list);
    for(int i=0;i<no_of_linked_list;i++){
        struct Node* head=NULL;
        head=val_in_linked_list(head);
        printf("Orignal List:");
        printing(head);
        head=reverse(head);
        printf("Reversed List:");
        printing(head);

    }
return 0;
    }

