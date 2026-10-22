#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[50];
    char designation[50];
    int manager_id; /* 0 means no manager */
    int active;
} Employee;

Employee employees[MAX];
int count = 0;

Employee *find_employee(int id) {
    Employee *employee = employees;
    Employee *end = employees + count;

    while (employee < end) {
        if (employee->active && employee->id == id)
            return employee;
        employee++;
    }
    return NULL;
}

void add_employee(void) {
    Employee *employee;
    int manager_id;

    if (count == MAX) {
        printf("Employee list is full.\n");
        return;
    }

    employee = &employees[count];

    printf("Employee ID: ");
    scanf("%d", &employee->id);
    getchar(); 
    if (employee->id == 0) {
        puts("Employee ID 0 is reserved for top-level employees.");
        return;
    }
    if (find_employee(employee->id) != NULL) {
        puts("ID already exists.");
        return;
    }

    printf("Name: ");
    if (fgets(employee->name, sizeof employee->name, stdin) == NULL) return;
    employee->name[strcspn(employee->name, "\n")] = '\0';
    printf("Designation: ");
    if (fgets(employee->designation, sizeof employee->designation, stdin) == NULL) return;
    employee->designation[strcspn(employee->designation, "\n")] = '\0';
    printf("Manager ID (0 for top-level): ");
    scanf("%d", &manager_id);

    if (manager_id != 0 && find_employee(manager_id) == NULL) {
        puts("Manager not found.");
        return;
    }

    employee->manager_id = manager_id;
    employee->active = 1;
    count++;
    puts("Employee added.");
}

void remove_employee(void) {
    int id;
    Employee *employee;
    Employee *current = employees;
    Employee *end = employees + count;

    printf("Employee ID to remove: ");
    scanf("%d", &id);
    employee = find_employee(id);
    if (employee == NULL) {
        puts("Employee not found.");
        return;
    }

    /* Direct reports take the removed employee's manager ID. */
    while (current < end) {
        if (current->active && current->manager_id == employee->id)
            current->manager_id = employee->manager_id;
        current++;
    }
    employee->active = 0;
    puts("Removed. Their employees now report to the former manager, or are top-level.");
}

/* Recursively print this employee and all direct and indirect reports. */
void display_hierarchy(Employee *employee, int indent) {
    Employee *current = employees;
    Employee *end = employees + count;
    int level = 0;

    while (level < indent) {
        printf("  ");
        level++;
    }
    printf("%d - %s - %s\n", employee->id,
           employee->name, employee->designation);

    while (current < end) {
        if (current->active && current->manager_id == employee->id)
            display_hierarchy(current, indent + 1);
        current++;
    }
}

/* Recursively count employees below this employee, excluding this employee. */
int count_reports(Employee *employee) {
    Employee *current = employees;
    Employee *end = employees + count;
    int total = 0;

    while (current < end) {
        if (current->active && current->manager_id == employee->id)
            total += 1 + count_reports(current);
        current++;
    }
    return total;
}

void display_one_hierarchy(void) {
    int id;
    Employee *employee;

    printf("Employee ID: ");
    scanf("%d", &id);
    employee = find_employee(id);
    if (employee == NULL) {
        puts("Employee not found.");
        return;
    }

    display_hierarchy(employee, 0);
    printf("Total Employees Under %d: %d\n", employee->id, count_reports(employee));
}

/* Recursively print a branch and return its employee count. */
int display_complete_branch(Employee *employee) {
    Employee *current = employees;
    Employee *end = employees + count;
    int total = 1;

    printf("%d - %s - %s\n", employee->id,
           employee->name, employee->designation);
    while (current < end) {
        if (current->active && current->manager_id == employee->id)
            total += display_complete_branch(current);
        current++;
    }
    return total;
}

void display_complete_hierarchy(void) {
    Employee *employee = employees;
    Employee *end = employees + count;
    int total = 0;

    printf("===== ORGANIZATION HIERARCHY =====\n");
    while (employee < end) {
        if (employee->active && employee->manager_id == 0)
            total += display_complete_branch(employee);
        employee++;
    }
    printf("Total Employees: %d\n", total);
}

int main(void) {
    int choice;

    do {
        printf("\n===== EMPLOYEE HIERARCHY MANAGEMENT =====\n");
        printf("1. Add Employee\n2. Remove Employee\n");
        printf("3. Display Employee Hierarchy\n4. Display Complete Hierarchy\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_employee(); break;
            case 2: remove_employee(); break;
            case 3: display_one_hierarchy(); break;
            case 4: display_complete_hierarchy(); break;
            case 5: puts("Goodbye."); break;
            default: puts("Invalid choice.");
        }
    } while (choice != 5);

    return 0;
}
