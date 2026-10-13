#include<stdio.h>
#include<string.h>
int main(){
    const int STANDARD = 150;
    const int PREMIUM = 250;
    const int RECLINER = 400;
    char customer_name[50],category[20];
    int  number_of_tickets,ticket_category;
    float sub_total,discount=0,final_bill;
    scanf("%s",customer_name);
    scanf("%d",&number_of_tickets);
    scanf("%d",&ticket_category);
    switch (ticket_category){
    case 1:
        strcpy(category, "Standard");
        sub_total=STANDARD*number_of_tickets;
        break;
    case 2:
        strcpy(category, "Preminum");
        sub_total=PREMIUM*number_of_tickets;
        break;
    case 3:
        strcpy(category, "Recliner");
        sub_total=RECLINER*number_of_tickets;
        break;
    default:
            printf("Invalid Category");
            return 1;
    
    }
    printf("Customer:%s\nTicket Category: %s\nTickets:%d\n",customer_name,category,number_of_tickets);
    printf("Subtotal:%.2f\n",sub_total);
    if (number_of_tickets>=5){
        discount=sub_total*(0.1);
    }
    printf("Discount:%.2f\n",discount);
    printf("Final Bill:%.2f",sub_total-discount);
    return 0;
}
