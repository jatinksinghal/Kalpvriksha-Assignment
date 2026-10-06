/* Simple user record CRUD program */
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "users.txt"

typedef struct {
    int id;
    char name[50];
    int age;
} User;

void createFile(void) {
    FILE *file = fopen(FILE_NAME, "a");
    if (file != NULL) fclose(file);
}

void addUser(void) {
    FILE *file;
    User user, oldUser;

    printf("Enter ID: ");
    scanf("%d", &user.id);
    file = fopen(FILE_NAME, "r");

    /* Check that the ID is unique. */
    while (file != NULL && fscanf(file, "%d %49s %d", &oldUser.id,
                                  oldUser.name, &oldUser.age) == 3) {
        if (oldUser.id == user.id) {
            printf("ID already exists.\n");
            fclose(file);
            return;
        }
    }
    if (file != NULL) fclose(file);

    printf("Enter name: ");
    scanf("%49s", user.name);
    printf("Enter age: ");
    scanf("%d", &user.age);

    file = fopen(FILE_NAME, "a");
    fprintf(file, "%d %s %d\n", user.id, user.name, user.age);
    fclose(file);
    printf("User added.\n");
}

void displayUsers(void) {
    FILE *file = fopen(FILE_NAME, "r");
    User user;
    int found = 0;

    printf("\nID\tName\tAge\n------------------------\n");
    while (file != NULL && fscanf(file, "%d %49s %d", &user.id,
                                  user.name, &user.age) == 3) {
        printf("%d\t%s\t%d\n", user.id, user.name, user.age);
        found = 1;
    }
    if (!found) printf("No users found.\n");
    if (file != NULL) fclose(file);
}

void updateUser(void) {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    User user;
    int id, found = 0;

    printf("Enter ID to update: ");
    scanf("%d", &id);

    while (file != NULL && fscanf(file, "%d %49s %d", &user.id,
                                  user.name, &user.age) == 3) {
        if (user.id == id) {
            printf("Enter new name: ");
            scanf("%49s", user.name);
            printf("Enter new age: ");
            scanf("%d", &user.age);
            found = 1;
        }
        fprintf(temp, "%d %s %d\n", user.id, user.name, user.age);
    }

    if (file != NULL) fclose(file);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    printf(found ? "User updated.\n" : "User not found.\n");
}

void deleteUser(void) {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    User user;
    int id, found = 0;

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (file != NULL && fscanf(file, "%d %49s %d", &user.id,
                                  user.name, &user.age) == 3) {
        if (user.id == id) {
            found = 1;
        } else {
            fprintf(temp, "%d %s %d\n", user.id, user.name, user.age);
        }
    }

    if (file != NULL) fclose(file);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
    printf(found ? "User deleted.\n" : "User not found.\n");
}

int main(void) {
    int choice;
    createFile();

    do {
        printf("\n1. Add User\n2. Display Users\n3. Update User\n"
               "4. Delete User\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) addUser();
        else if (choice == 2) displayUsers();
        else if (choice == 3) updateUser();
        else if (choice == 4) deleteUser();
        else if (choice != 5) printf("Invalid choice.\n");
    } while (choice != 5);

    return 0;
}
