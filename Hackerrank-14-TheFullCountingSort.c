#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void countSort(int arr_rows, int arr_columns, char*** arr) {
    char **bucket[100];
    int count[100]={0};
    for(int i=0;i<arr_rows;i++){
        int key=atoi(arr[i][0]);
        count[key]++;
    }
    for(int i=0;i<100;i++){
        if(count[i]>0){
            bucket[i]=malloc(count[i]*sizeof(char*));
            count[i]=0;
        }
    }
    for(int i=0;i<arr_rows;i++){
        int key=atoi(arr[i][0]);
        if(i<arr_rows/2)
            bucket[key][count[key]++] = "-";
        else bucket[key][count[key]++]=arr[i][1];
    }
    for(int i=0;i<100;i++){
        for(int j=0;j<count[i];j++){
            printf("%s ",bucket[i][j]);
        }
        if(count[i]>0) free(bucket[i]);
    }
    printf("\n");
}
int main()
{
    int n;

    printf("Enter number of pairs: ");
    scanf("%d", &n);

    char ***arr = malloc(n * sizeof(char**));

    if(arr == NULL)
        return 1;
    for(int i = 0; i < n; i++)
    {
        arr[i] = malloc(2 * sizeof(char*));

        arr[i][0] = malloc(1000 * sizeof(char));
        arr[i][1] = malloc(1000 * sizeof(char));

        if(arr[i] == NULL || arr[i][0] == NULL || arr[i][1] == NULL)
            return 1;

        printf("Enter integer and string: ");
        scanf("%999s %999s", arr[i][0], arr[i][1]);
    }


    countSort(n, 2, arr);


    for(int i = 0; i < n; i++)
    {
        free(arr[i][0]);
        free(arr[i][1]);
        free(arr[i]);
    }

    free(arr);

    return 0;
}
