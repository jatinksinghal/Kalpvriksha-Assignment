#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void genrate_matrix(int n,int arr[n][n]){
    srand(time(NULL));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
        *(*(arr + i) + j) = rand() % 256;
        }}
}
void show_matrix(int n,int arr[n][n]){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%3d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
}
void rotated_matrix(int n,int arr[n][n]){
    int temp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            temp = *(*(arr + i) + j);

            *(*(arr + i) + j) = *(*(arr + j) + i);
            *(*(arr + j) + i) = temp;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            int *left = *(arr + i) + j;
            int *right = *(arr + i) + (n - 1 - j);

            temp = *left;
            *left = *right;
            *right = temp;
        }
    }
}
void smoothening_filter(int n,int arr[n][n]){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0, count = 0;
            for (int r = i - 1; r <= i + 1; r++) {
                for (int c = j - 1; c <= j + 1; c++) {
                    if (r >= 0 && r < n &&
                        c >= 0 && c < n) {
                        int *p = *(arr + r) + c;
                        sum += *p;
                        count++;
                    }
                }
            }
            int *p = *(arr + i) + j;
            *p = sum / count;
        }
    }
}
int main(){
    int num;
    printf("Enter matrix size (2-10):");
    scanf("%d",&num);
    if(num>10 || num<2) {
        printf("Invalid Input");
        return 0;
    }
    int arr[num][num];
    genrate_matrix(num,arr);
    printf("Orignal:\n");
    show_matrix(num,arr);
    rotated_matrix(num,arr);
    printf("Rotated 90 degree clockwise degree:\n");
    show_matrix(num,arr);
    printf("Final Output:\n");
    smoothening_filter(num,arr);
    show_matrix(num,arr);
}
