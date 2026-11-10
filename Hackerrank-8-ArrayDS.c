#include <stdio.h>
#include<stdlib.h>
#include<limits.h>
int hourglassSum(int arr_rows, int arr_columns, int** arr) {
    int max=-10000;
for(int i=0;i<arr_rows-2;i++){
    for(int j=0;j<arr_columns-2;j++){
        int sum=*(*(arr+i)+j)+ *(*(arr+i)+j+1)+ *(*(arr+i)+j+2)+ *(*(arr+i+1)+j+1)+ *(*(arr+i+2)+j)+ *(*(arr+i+2)+j+1)+ *(*(arr+i+2)+j+2);
        if (sum>max){
            max=sum;
        }
        printf("%d ",sum);  
    }
}

return max;
}

int main()
{
  int arr_rows,arr_columns;
  printf("Enter no. of Row:");
  scanf("%d",&arr_rows);
  printf("Enter no. of Column:");
  scanf("%d",&arr_columns);
  if(arr_columns <3 || arr_rows<3 ){
    printf("Less than 3 rows or collumn");
    return 0;
  }

    int **arr = malloc(arr_rows * sizeof(int*));

    for (int i = 0; i < arr_rows; i++) {
        *(arr+i) = malloc(arr_columns * (sizeof(int)));

        for (int j = 0; j < arr_columns; j++) {

            scanf("%d",&(*(*(arr + i) + j)));
        }
    }

    int result = hourglassSum(arr_rows,arr_columns , arr);
    printf("\nMax Value of Hour glass is:%d",result);
    for(int i=0; i<arr_rows; i++)
{
    free(arr[i]);
}
    free(arr);
    return 0;
}
