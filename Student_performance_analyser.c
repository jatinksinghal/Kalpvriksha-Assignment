#include<stdio.h>
#include<string.h>
struct student{
    int R_no;
    char Name[50];
    int Total;
    float Avg;
    char Grade;
};
int CalculateTotal(int a,int b,int c){
    return (a+b+c);
}
float CalculateAvg(int total){
    return total/3.0;
}
char calculateGrade(float avg) {
    if (avg >= 85)
        return 'A';
    else if (avg >= 70)
        return 'B';
    else if (avg >= 50)
        return 'C';
    else if (avg >= 35)
        return 'D';
    else
        return 'F';
}
void recursion(int initial,int num){
    if(initial>num) 
        return;
    printf("%d\n",initial);
    recursion(initial+1,num);
}
int main(){
    int num;
    printf("Enter no Students:");
    scanf("%d",&num);
    struct student Student[num];
    for(int i=0;i<num;i++){
            int roll, m1,m2,m3,total;
            float average;
            char name[50];
            printf("Roll No: | Name\t|Marks1\t|Marks2\t|Marks3\n");
            scanf("%d %s %d %d %d",&roll,name,&m1,&m2,&m3);
            total=CalculateTotal(m1, m2, m3);
            average=CalculateAvg(total);
            strcpy(Student[i].Name, name);
            Student[i].R_no=roll;
            Student[i].Total=total;
            Student[i].Avg=average;
            Student[i].Grade=calculateGrade(average);       
    }
    for(int i=0;i<num;i++){
        printf("Roll No:%d\nName:%s\nTotal:%d\nAverage:%f\nGrade:%c\n",Student[i].R_no,Student[i].Name,Student[i].Total,Student[i].Avg,Student[i].Grade);
        if (Student[i].Avg>=85) printf("Performance: *****\n");
        else if (Student[i].Avg>=70) printf("Performance: ****\n");
        else if (Student[i].Avg>=50) printf("Performance: ***\n");
        else if (Student[i].Avg>=35) printf("Performance: **\n");
        printf("\n");
    }
    printf("List of Roll Numbers (via recursion):\n");
    recursion(1,num);
    return 0;
}