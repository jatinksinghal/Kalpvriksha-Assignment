// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include "Players_data.h"
// #define MAX_TEAMS 10
// #define MAX_PLAYERS 500
// struct Players
// {
//     int ID;
//     char Name[50];
//     char Team[20];
//     int Role;
//     int run;
//     float avg;
//     float SR;
//     int wickets;
//     float ER;
//     float pref_index;
//     struct Players* next;
// };
// struct Team{
//     int ID;
//     char Name[50];
//     int total_player;
//     float average_batting_rate;
//     struct Players* head;
//     struct Players* rolePlayers[3][MAX_PLAYERS];
//     int roleCount[3];
// };
// struct Team teamRecords[MAX_TEAMS];

// void Add_player(){
//     int id,pid,role,total_run,wickets;
//     printf("\nEnter Team ID to add player:");
//     scanf("%d",&id);
//     if(id<1 || id>10){
//         printf("Invalid ID\n");
//         return;
//     }
//     printf ("\nEnter Player Details:");
//     printf("\nPlayer ID:");
//     scanf("%d",)
//     printf("\nName:");
//     printf("\nRole (1-Batsman, 2-Bowler, 3-All-rounder):");
//     printf("\nTotal Runs:");
//     printf("\nBatting Average:");
//     printf("\nStrike Rate:");
//     printf("\nWickets:");
//     printf("\nEconomy Rate:");

// }
// int main(){
//     int choice;
//     do {
//     printf("1. Add Player to Team\n");
//     printf("2. Display Players of a Specific Team\n");
//     printf("3. Display Teams by Average Batting Strike Rate\n");
//     printf("4. Display Top K Players of a Specific Team by Role\n");
//     printf("5. Display all Players of specific role Across All Teams by performance index\n");
//     printf("6. Exit\n");
//     printf("Enter your choice:");
//     scanf("%d",&choice);
//     switch (choice)
//     {
//     case 1:
//         /* code */
//         break;
//     case 2:
//         /* code */
//         break;
//     case 3:
//         /* code */
//         break;
//     case 4:
//         /* code */
//         break;
//     case 5:
//         /* code */
//         break; 
//     case 6:
//         /* code */
//         break;       
//     default:
//     printf("Invalid Input\n");
//         break;
//     }
//     while (choice!=6)
//     {
//         printf("Exiting Program\n");
//     }
    
//     }
// }



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Players_data.h"

#define MAX_TEAMS 10
#define MAX_PLAYERS 5000

struct Players
{
    int ID;
    char Name[50];
    char Team[50];
    int Role;
    int run;
    float avg;
    float SR;
    int wickets;
    float ER;
    float pref_index;
    struct Players* next;
};

struct Team
{
    int ID;
    char Name[50];
    int total_player;
    float average_batting_rate;
    struct Players* head;
};

struct Team team[10];

int getRole(const char* role)
{
    if(strcmp(role, "Batsman") == 0)
        return 1;
    if(strcmp(role, "Bowler") == 0)
        return 2;
    return 3;
}

char* roleName(int role)
{
    if(role == 1)
        return "Batsman";
    if(role == 2)
        return "Bowler";
    return "All-rounder";
}

float calculateIndex(struct Players* p)
{
    if(p->Role == 1)
        return (p->avg * p->SR) / 100;

    if(p->Role == 2)
        return (p->wickets * 2) + (100 - p->ER);

    return ((p->avg * p->SR) / 100) + (p->wickets * 2);
}

void initializeTeams()
{
    for(int i = 0; i < MAX_TEAMS; i++)
    {
        team[i].ID = i + 1;
        strcpy(team[i].Name, teams[i]);
        team[i].total_player = 0;
        team[i].average_batting_rate = 0;
        team[i].head = NULL;
    }
}

int findTeam(int id)
{
    for(int i = 0; i < MAX_TEAMS; i++)
    {
        if(team[i].ID == id)
            return i;
    }
    return -1;
}

int playerExists(int id)
{
    for(int i = 0; i < MAX_TEAMS; i++)
    {
        struct Players* temp = team[i].head;

        while(temp != NULL)
        {
            if(temp->ID == id)
                return 1;

            temp = temp->next;
        }
    }
    return 0;
}

void insertPlayer(struct Players* newnode, int index)
{
    struct Players* temp = team[index].head;

    if(temp == NULL)
    {
        team[index].head = newnode;
    }
    else
    {
        while(temp->next != NULL)
            temp = temp->next;

        temp->next = newnode;
    }

    team[index].total_player++;
}

void updateAverage(int index)
{
    struct Players* temp = team[index].head;
    float total = 0;
    int count = 0;

    while(temp != NULL)
    {
        if(temp->Role == 1 || temp->Role == 3)
        {
            total += temp->SR;
            count++;
        }

        temp = temp->next;
    }

    if(count > 0)
        team[index].average_batting_rate = total / count;
    else
        team[index].average_batting_rate = 0;
}

void loadPlayers()
{
    for(int i = 0; i < playerCount; i++)
    {
        struct Players* p = malloc(sizeof(struct Players));

        if(p == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }

        p->ID = players[i].id;
        strcpy(p->Name, players[i].name);
        strcpy(p->Team, players[i].team);
        p->Role = getRole(players[i].role);
        p->run = players[i].totalRuns;
        p->avg = players[i].battingAverage;
        p->SR = players[i].strikeRate;
        p->wickets = players[i].wickets;
        p->ER = players[i].economyRate;
        p->pref_index = calculateIndex(p);
        p->next = NULL;

        for(int j = 0; j < MAX_TEAMS; j++)
        {
            if(strcmp(team[j].Name, p->Team) == 0)
            {
                insertPlayer(p, j);
                break;
            }
        }
    }

    for(int i = 0; i < MAX_TEAMS; i++)
        updateAverage(i);
}

void Add_player()
{
    int id, role;
    struct Players* p = malloc(sizeof(struct Players));

    if(p == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Enter Team ID: ");
    scanf("%d", &id);

    int index = findTeam(id);

    if(index == -1)
    {
        printf("Invalid Team ID\n");
        free(p);
        return;
    }

    printf("Enter Player ID: ");
    scanf("%d", &p->ID);

    if(p->ID <= 0 || playerExists(p->ID))
    {
        printf("Invalid or duplicate Player ID\n");
        free(p);
        return;
    }

    printf("Enter Name: ");
    scanf(" %49[^\n]", p->Name);

    strcpy(p->Team, team[index].Name);

    printf("Role (1-Batsman, 2-Bowler, 3-All-rounder): ");
    scanf("%d", &role);

    if(role < 1 || role > 3)
    {
        printf("Invalid Role\n");
        free(p);
        return;
    }

    p->Role = role;

    printf("Total Runs: ");
    scanf("%d", &p->run);

    printf("Batting Average: ");
    scanf("%f", &p->avg);

    printf("Strike Rate: ");
    scanf("%f", &p->SR);

    printf("Wickets: ");
    scanf("%d", &p->wickets);

    printf("Economy Rate: ");
    scanf("%f", &p->ER);

    p->pref_index = calculateIndex(p);
    p->next = NULL;

    insertPlayer(p, index);
    updateAverage(index);

    printf("Player added successfully!\n");
    printf("Performance Index: %.2f\n", p->pref_index);
}

void displayTeam()
{
    int id;

    printf("Enter Team ID: ");
    scanf("%d", &id);

    int index = findTeam(id);

    if(index == -1)
    {
        printf("Invalid Team ID\n");
        return;
    }

    struct Players* temp = team[index].head;

    printf("\nTeam: %s\n", team[index].Name);
    printf("Total Players: %d\n", team[index].total_player);

    while(temp != NULL)
    {
        printf("\nID: %d", temp->ID);
        printf("\nName: %s", temp->Name);
        printf("\nRole: %s", roleName(temp->Role));
        printf("\nRuns: %d", temp->run);
        printf("\nStrike Rate: %.2f\n", temp->SR);

        temp = temp->next;
    }

    printf("\nAverage Batting Strike Rate: %.2f\n",
           team[index].average_batting_rate);
}

void displayTeams()
{
    struct Team* arr[10];

    for(int i = 0; i < MAX_TEAMS; i++)
        arr[i] = &team[i];

    for(int i = 0; i < MAX_TEAMS - 1; i++)
    {
        for(int j = 0; j < MAX_TEAMS - i - 1; j++)
        {
            if(arr[j]->average_batting_rate <
               arr[j + 1]->average_batting_rate)
            {
                struct Team* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("\nTeams Sorted by Average Batting Strike Rate\n");

    for(int i = 0; i < MAX_TEAMS; i++)
    {
        printf("\n%d. %s", arr[i]->ID, arr[i]->Name);
        printf("\nPlayers: %d", arr[i]->total_player);
        printf("\nAverage SR: %.2f\n",
               arr[i]->average_batting_rate);
    }
}

void displayTopK()
{
    int id, role, k;
    struct Players* arr[MAX_PLAYERS];
    int count = 0;

    printf("Enter Team ID: ");
    scanf("%d", &id);

    int index = findTeam(id);

    if(index == -1)
    {
        printf("Invalid Team ID\n");
        return;
    }

    printf("Enter Role (1-Batsman, 2-Bowler, 3-All-rounder): ");
    scanf("%d", &role);

    if(role < 1 || role > 3)
    {
        printf("Invalid Role\n");
        return;
    }

    printf("Enter K: ");
    scanf("%d", &k);

    if(k <= 0)
    {
        printf("Invalid K\n");
        return;
    }

    struct Players* temp = team[index].head;

    while(temp != NULL)
    {
        if(temp->Role == role && count < MAX_PLAYERS)
        {
            arr[count] = temp;
            count++;
        }

        temp = temp->next;
    }

    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(arr[j]->pref_index < arr[j + 1]->pref_index)
            {
                struct Players* p = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = p;
            }
        }
    }

    if(k > count)
        k = count;

    printf("\nTop %d Players:\n", k);

    for(int i = 0; i < k; i++)
    {
        printf("\nID: %d", arr[i]->ID);
        printf("\nName: %s", arr[i]->Name);
        printf("\nPerformance Index: %.2f\n",
               arr[i]->pref_index);
    }
}

void displayAllRolePlayers()
{
    int role;
    struct Players* arr[MAX_PLAYERS];
    int count = 0;

    printf("Enter Role (1-Batsman, 2-Bowler, 3-All-rounder): ");
    scanf("%d", &role);

    if(role < 1 || role > 3)
    {
        printf("Invalid Role\n");
        return;
    }

    for(int i = 0; i < MAX_TEAMS; i++)
    {
        struct Players* temp = team[i].head;

        while(temp != NULL)
        {
            if(temp->Role == role && count < MAX_PLAYERS)
            {
                arr[count] = temp;
                count++;
            }

            temp = temp->next;
        }
    }

    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(arr[j]->pref_index < arr[j + 1]->pref_index)
            {
                struct Players* p = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = p;
            }
        }
    }

    printf("\nAll %s Players:\n", roleName(role));

    for(int i = 0; i < count; i++)
    {
        printf("\nID: %d", arr[i]->ID);
        printf("\nName: %s", arr[i]->Name);
        printf("\nTeam: %s", arr[i]->Team);
        printf("\nPerformance Index: %.2f\n",
               arr[i]->pref_index);
    }
}

void freePlayers()
{
    for(int i = 0; i < MAX_TEAMS; i++)
    {
        struct Players* temp = team[i].head;

        while(temp != NULL)
        {
            struct Players* next = temp->next;
            free(temp);
            temp = next;
        }
    }
}

int main()
{
    int choice;

    initializeTeams();
    loadPlayers();

    printf("\nICC ODI Player Performance Analyzer\n");
    printf("Loaded %d Players\n", playerCount);

    do
    {
        printf("\n1. Add Player to Team");
        printf("\n2. Display Players of a Team");
        printf("\n3. Display Teams by Average Strike Rate");
        printf("\n4. Display Top K Players by Role");
        printf("\n5. Display All Players of a Role");
        printf("\n6. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                Add_player();
                break;

            case 2:
                displayTeam();
                break;

            case 3:
                displayTeams();
                break;

            case 4:
                displayTopK();
                break;

            case 5:
                displayAllRolePlayers();
                break;

            case 6:
                printf("Exiting Program\n");
                break;

            default:
                printf("Invalid Choice\n");
        }

    } while(choice != 6);

    freePlayers();

    return 0;
}
