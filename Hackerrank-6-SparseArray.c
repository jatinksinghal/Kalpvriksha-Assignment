#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* matchingStrings(int stringList_count, char stringList[][50], int queries_count, char queries[][50], int* result_count) {
    *result_count=queries_count;
    int result[queries_count];
    for(int i=0;i<queries_count;i++){
        int count=0;
        for(int j=0;j<stringList_count;j++){
            if(strcmp(queries[i],stringList[j])==0) count++;
        }
        result[i]=count;
    }
    return result;
}

int main()
{
    int stringList_count,queries_count, result_count;
    scanf("%d",&stringList_count);
    char stringList[stringList_count][50];
    for(int i=0;i<stringList_count;i++){
        scanf("%49s",stringList[i]);
    }
    getchar();
    scanf("%d",&queries_count);
    char queries[queries_count][50];
    for (int i = 0; i < queries_count; i++)
    {
       scanf("%49s",queries[i]);
    }
    int* result_arr = matchingStrings(stringList_count,stringList,queries_count , queries, &result_count);

    for(int i = 0; i < result_count; i++){
    printf("\n%d", result_arr[i]);
    }
    return 0;
    

}

