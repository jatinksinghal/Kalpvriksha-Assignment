#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int find_nth_term(int n, int a, int b, int c) {
  if(n==1) return a;
  else if(n==2) return b;
  else if(n==3) return c;
  else {
    return find_nth_term(n-1,b,c,a+b+c);
  }
}

int main() {
    int n, a, b, c;
    printf("Enter Nth term");
     scanf("%d", &n);
    printf("Enter 1st element");
     scanf("%d",&a);
    printf("Enter 2nd element");
     scanf("%d"&b);
    printf("Enter 3rd element");
    scanf("%d",&c);
    int ans = find_nth_term(n, a, b, c);
    printf("%d", ans); 
    return 0;
}

