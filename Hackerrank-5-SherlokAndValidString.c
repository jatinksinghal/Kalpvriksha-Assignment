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

char* readline();
char* isValid(char* s) {
    int freq[26]={0};
    for(int i=0;s[i]!='\0';i++){
        freq[s[i]-'a']++;
    }
    int count[100001]={0};
    for(int i=0;i<26;i++){
        if (freq[i]>0) count[freq[i]]++;
    }
    int distinct=0,min=100001,max=0;
    for(int i=0;i<100001;i++){
        if(count[i]>0){
            distinct++;
            if(i>max) max=i;
            if(i<min) min=i;
        }
    }
    if (distinct == 1)
    return "YES";

if (distinct == 2) {
    if (max - min == 1 && count[max] == 1)
        return "YES";

    if (max - min == 1 && count[min] == 1)
        return "YES";

    if (min == 1 && count[min] == 1)
        return "YES";
}

return "NO";
}

int main()
{
    char string[100001],result[10];
    printf("Enter a String: ");
    scanf("%s",string);
    strcpy(result,isValid(string));
    printf("%s",result);
    return 0;
}






