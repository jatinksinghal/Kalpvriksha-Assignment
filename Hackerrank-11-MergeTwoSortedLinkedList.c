#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data;
    struct Node *next;
};
struct Node* insert_Val_in_node(struct Node *head){
    int num;
    struct Node *temp=NULL,*newnode=NULL;
    printf("Enter No Of Nodes:");
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
struct Node* mergeLists(struct Node* head1, struct Node* head2)
 {
    if(head1 == NULL)
        return head2;

    if(head2 == NULL)
        return head1;

    struct Node *head = NULL;
    struct Node *tail = NULL;

    while(head1 != NULL && head2 != NULL)
    {
        struct Node *temp;

        if(head1->data <= head2->data)
        {
            temp = head1;
            head1 = head1->next;
        }
        else
        {
            temp = head2;
            head2 = head2->next;
        }

        if(head == NULL)
        {
            head = temp;
            tail = temp;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }
    }

    if(head1 != NULL)
        tail->next = head1;

    if(head2 != NULL)
        tail->next = head2;

    return head;
}
struct Node* printing(struct Node * merged){
    while (merged!=NULL)
    {
        printf("%d->",merged->data);
        merged=merged->next;
    }
    printf("NULL\n");
    
}
void sortList(struct Node *head){
    struct Node *temp;
    for(temp=head; temp->next!=NULL; temp=temp->next){
        for(struct Node *p=head; p->next!=NULL; p=p->next){
            if(p->data>p->next->data){
                int swap=p->data;
                p->data=p->next->data;
                p->next->data=swap;
            }
        }
    }
}

int main(){
    struct Node *head1=NULL,*head2=NULL,*merged=NULL;
    head1=insert_Val_in_node(head1);
    printf("Orignal Node 1:");
    printing(head1);
    sortList(head1);
    printf("Sorted Node 1:");
    printing(head1);
    head2=insert_Val_in_node(head2);
    printf("Orignal Node 2:");
    printing(head2);
    sortList(head2);
    printf("Sorted Node 2:");
    printing(head2);
    printf("Merged List:");
    merged=mergeLists(head1,head2);
    printing(merged);
    return 0;
}
