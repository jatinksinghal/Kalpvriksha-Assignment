#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void calculate_the_maximum(int n, int k) {
  int xor=0,or=0,and=0;
  for(int i=1;i<n;i++){
    for(int j=i+1;j<=n;j++){
        int temp_and,temp_or,temp_xor;
        temp_and=i&j;
        temp_or=i|j;
        temp_xor=i^j;
        and=((temp_and>=and) &&(temp_and<k))?temp_and:and;
        or=((temp_or>=or) &&(temp_or<k))?temp_or:or;
        xor=((temp_xor>=xor) &&(temp_xor<k))?temp_xor:xor;
    }
  }
  printf("Maximum value of AND<Constant:%d\nMax value of OR<Constan:t%d\nMax value of XOR<Constant:%d",and,or,xor);
}

int main() {
    int number, k;
    printf("Enter Nunber:");
    scanf("%d",&number);
    printf("Enter Constant:");
    scanf("%d",&k);
    calculate_the_maximum(n, k);
    return 0;
}
