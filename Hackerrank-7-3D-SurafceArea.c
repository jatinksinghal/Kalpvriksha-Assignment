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


int surfaceArea(int A_rows, int A_columns, int A[A_rows][A_columns]) {
  int area = 0;
    for(int i=0; i<A_rows; i++){
        for(int j=0; j<A_columns; j++){
            if((A[i][j])!=0) area+=2;
            else continue;
            if(j+1<A_columns)
                  area += A[i][j]>A[i][j+1]?A[i][j]-A[i][j+1]:0;
            else
                  area += A[i][j];  
            if(j-1>=0)          
                  area += A[i][j]>A[i][j-1]?A[i][j]-A[i][j-1]:0;
            else
                  area += A[i][j];
            if(i+1<A_rows)                 
                  area += A[i][j]>A[i+1][j]?A[i][j]-A[i+1][j]:0;
            else
                  area += A[i][j];
            if(i-1>=0)      
                  area += A[i][j]>A[i-1][j]?A[i][j]-A[i-1][j]:0;
            else
                  area += A[i][j];
        }
    }
    return area;

}

int main()
{
    int A_row, A_column;
    scanf("%d %d", &A_row, &A_column);
    int A[100][100];
    for (int i=0;i<A_row;i++){
        for(int j =0;j<A_column;j++){
            scanf("%d", &A[i][j]);
        }
    }
    int result = surfaceArea(A_row, A_column, A);
    printf("\n%d",result);
    return 0;  

}

