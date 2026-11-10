#include <stdio.h>
#include <stdlib.h>

long arrayManipulation(int n, int queries_rows, int queries_columns, int** queries) {
    long *arr= calloc(n,sizeof(long));
    for(int i=0;i<queries_rows;i++){
        int a=queries[i][0],b=queries[i][1],c=queries[i][2];
        arr[a-1]+=c;
        arr[b]-=c;
    }
    long max=0,sum=0;
    for(int i=0;i<n;i++){
        sum+=arr[i];
        if (sum>max){
            max=sum;
        }
    }
    free(arr);
    return max;
}

int main()
{   
    int arr_size,no_of_queries;
    printf("Enter Size Of Array:");
    scanf("%d",&arr_size);
    printf("\nEnter No. Of Queries:");
    scanf("%d",&no_of_queries);
    printf("Enter Queries:\n");
    int** queries=malloc(arr_size*sizeof(int*));
    for (int i = 0; i < no_of_queries; i++) {
        *(queries + i) = malloc(3 * (sizeof(int)));


        for (int j = 0; j < 3; j++) {
            
            scanf("%d",&*(*(queries + i) + j));
        }
    }

    long result = arrayManipulation(arr_size, no_of_queries, 3, queries);
    printf("%ld",result);
    for(int i=0;i<no_of_queries;i++){
        free(*(queries+i));
    }
    free(queries);

    return 0;
}
