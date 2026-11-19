#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node* next;
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
int has_cycle(struct Node* head) {
struct Node *slow=head;
struct Node *fast=head;
while(fast!=NULL &&fast->next!=NULL){
    slow=slow->next;
    fast=fast->next->next;
    if(slow==fast) return 1;
}
return 0;
}
int main(){
    int num;
    printf("No of Linked List");
    scanf("%d",&num);
    for(int i=0;i<num;i++){
        struct Node*head=NULL;
        head=val_in_linked_list(head);
        printf("%d\n",has_cycle(head));
    }
    return 0;
}
