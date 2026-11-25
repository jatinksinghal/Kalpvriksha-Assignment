#include<stdio.h>
#include<stdlib.h>
int activityNotifications(int expenditure_count, int* expenditure, int d) {
    int count[201]={0};
    int t=0;
    for(int i=0;i<d;i++){
        count[expenditure[i]]++;
    }
    for(int i=d;i<expenditure_count;i++){
        int first=-1,secound=-1;
        int sum=0;
        for(int j=0;j<201;j++){
            sum+=count[j];
            if (first==-1 && sum>(d-1)/2){
                first=j;
            }
            if(sum>d/2){
                secound=j;
                break;
            }
        }
        int median;
        if(d%2==0){
            median=first+secound;
        }
        else median=2*first;
        if (expenditure[i]>=median) t++;
        count[expenditure[i-d]]--;
        count[expenditure[i]]++;
    }
    return t;
}
int main(){
    int size_arr,days;
    printf("Enter Size Of Array:");
    scanf("%d",&size_arr);
    printf("\nEnter No of Days:");
    scanf("%d",&days);
    int *arr=malloc(size_arr*sizeof(int));
    printf("Enter Elements in array:");
    for(int i=0;i<size_arr;i++){
        scanf("%d",&arr[i]);
    }
    printf("%d",activityNotifications(size_arr,arr,days));
    free(arr);
    return 0;
}
