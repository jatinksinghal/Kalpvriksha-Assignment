#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 512
#define NUM_BLOCKS 1024
#define MAX 4096

typedef struct File {
    char name[51];
    int isDirectory;
    int size;
    int count;
    int *blocks;
    struct File *parent;
    struct File *child;
    struct File *next;
    struct File *prev;
} File;

typedef struct Block {
    int index;
    struct Block *next;
    struct Block *prev;
} Block;

unsigned char (*disk)[BLOCK_SIZE];

File *root = NULL;
File *cwd = NULL;

Block *head = NULL;
Block *tail = NULL;

int freeCount = 0;

File *createNode(char name[], int type) {
    File *node = malloc(sizeof(File));

    if (node == NULL)
        return NULL;

    strcpy(node->name, name);
    node->isDirectory = type;
    node->size = 0;
    node->count = 0;
    node->blocks = NULL;
    node->parent = NULL;
    node->child = NULL;
    node->next = node;
    node->prev = node;

    return node;
}

void insertNode(File *parent, File *node) {
    node->parent = parent;

    if (parent->child == NULL) {
        parent->child = node;
    }
    else {
        File *last = parent->child->prev;

        last->next = node;
        node->prev = last;
        node->next = parent->child;
        parent->child->prev = node;
    }
}

void removeNode(File *node) {
    File *parent = node->parent;

    if (node->next == node) {
        parent->child = NULL;
    }
    else {
        node->prev->next = node->next;
        node->next->prev = node->prev;

        if (parent->child == node)
            parent->child = node->next;
    }

    node->parent = NULL;
}

File *findNode(char name[]) {
    if (cwd->child == NULL)
        return NULL;

    File *temp = cwd->child;

    do {
        if (strcmp(temp->name, name) == 0)
            return temp;

        temp = temp->next;

    } while (temp != cwd->child);

    return NULL;
}

void addBlock(int index) {
    Block *node = malloc(sizeof(Block));

    if (node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    node->index = index;
    node->next = NULL;
    node->prev = tail;

    if (head == NULL) {
        head = tail = node;
    }
    else {
        tail->next = node;
        tail = node;
    }

    freeCount++;
}

int getBlock() {
    if (head == NULL)
        return -1;

    Block *temp = head;
    int index = temp->index;

    head = head->next;

    if (head == NULL)
        tail = NULL;
    else
        head->prev = NULL;

    free(temp);
    freeCount--;

    return index;
}

void releaseBlocks(File *file) {
    for (int i = 0; i < file->count; i++) {
        addBlock(file->blocks[i]);
    }

    free(file->blocks);
    file->blocks = NULL;
    file->count = 0;
    file->size = 0;
}

int initialize() {
    disk = calloc(NUM_BLOCKS, sizeof(*disk));

    if (disk == NULL)
        return 0;

    for (int i = 0; i < NUM_BLOCKS; i++) {
        addBlock(i);
    }

    root = createNode("/", 1);

    if (root == NULL)
        return 0;

    cwd = root;

    return 1;
}

void mkdir(char name[]) {
    if (strlen(name) == 0 || strlen(name) > 50) {
        printf("Invalid name.\n");
        return;
    }

    if (findNode(name) != NULL) {
        printf("Name already exists.\n");
        return;
    }

    File *node = createNode(name, 1);

    if (node == NULL)
        return;

    insertNode(cwd, node);

    printf("Directory created successfully.\n");
}

void createFile(char name[]) {
    if (strlen(name) == 0 || strlen(name) > 50) {
        printf("Invalid name.\n");
        return;
    }

    if (findNode(name) != NULL) {
        printf("Name already exists.\n");
        return;
    }

    File *node = createNode(name, 0);

    if (node == NULL)
        return;

    insertNode(cwd, node);

    printf("File created successfully.\n");
}

void writeFile(char name[], char content[]) {
    File *file = findNode(name);

    if (file == NULL || file->isDirectory) {
        printf("File not found.\n");
        return;
    }

    int size = strlen(content);
    int required = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;

    if (required > freeCount + file->count) {
        printf("Disk is full.\n");
        return;
    }

    releaseBlocks(file);

    if (required > 0) {
        file->blocks = malloc(required * sizeof(int));

        if (file->blocks == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
    }

    file->count = required;
    file->size = size;

    int written = 0;

    for (int i = 0; i < required; i++) {
        int block = getBlock();

        if (block == -1) {
            printf("Block allocation failed.\n");
            releaseBlocks(file);
            return;
        }

        file->blocks[i] = block;

        int amount = size - written;

        if (amount > BLOCK_SIZE)
            amount = BLOCK_SIZE;

        memcpy(disk[block], content + written, amount);

        written += amount;
    }

    printf("Data written successfully.\n");
}

void readFile(char name[]) {
    File *file = findNode(name);

    if (file == NULL || file->isDirectory) {
        printf("File not found.\n");
        return;
    }

    if (file->size == 0) {
        printf("File is empty.\n");
        return;
    }

    int remaining = file->size;

    for (int i = 0; i < file->count; i++) {
        int amount = remaining;

        if (amount > BLOCK_SIZE)
            amount = BLOCK_SIZE;

        fwrite(disk[file->blocks[i]], 1, amount, stdout);

        remaining -= amount;
    }

    printf("\n");
}

void deleteFile(char name[]) {
    File *file = findNode(name);

    if (file == NULL || file->isDirectory) {
        printf("File not found.\n");
        return;
    }

    releaseBlocks(file);
    removeNode(file);
    free(file);

    printf("File deleted successfully.\n");
}

void rmdir(char name[]) {
    File *dir = findNode(name);

    if (dir == NULL || !dir->isDirectory) {
        printf("Directory not found.\n");
        return;
    }

    if (dir->child != NULL) {
        printf("Directory is not empty.\n");
        return;
    }

    removeNode(dir);
    free(dir);

    printf("Directory removed successfully.\n");
}

void ls() {
    if (cwd->child == NULL) {
        printf("(empty)\n");
        return;
    }

    File *temp = cwd->child;

    do {
        if (temp->isDirectory)
            printf("[DIR] %s\n", temp->name);
        else
            printf("[FILE] %s\n", temp->name);

        temp = temp->next;

    } while (temp != cwd->child);
}

void cd(char name[]) {
    if (strcmp(name, "/") == 0) {
        cwd = root;
        return;
    }

    if (strcmp(name, "..") == 0) {
        if (cwd->parent != NULL)
            cwd = cwd->parent;

        return;
    }

    File *dir = findNode(name);

    if (dir == NULL || !dir->isDirectory) {
        printf("Directory not found.\n");
        return;
    }

    cwd = dir;
}

void pwd() {
    File *path[100];
    int count = 0;

    File *temp = cwd;

    while (temp != root && count < 100) {
        path[count++] = temp;
        temp = temp->parent;
    }

    printf("/");

    for (int i = count - 1; i >= 0; i--) {
        printf("%s", path[i]->name);

        if (i != 0)
            printf("/");
    }

    printf("\n");
}

void df() {
    int used = NUM_BLOCKS - freeCount;

    printf("Total Blocks: %d\n", NUM_BLOCKS);
    printf("Used Blocks: %d\n", used);
    printf("Free Blocks: %d\n", freeCount);

    printf("Disk Usage: %.2f%%\n",
           (float)used / NUM_BLOCKS * 100);
}

void freeTree(File *node) {
    if (node == NULL)
        return;

    if (node->child != NULL) {
        File *first = node->child;
        File *temp = first;

        do {
            File *next = temp->next;
            freeTree(temp);
            temp = next;
        } while (temp != first);
    }

    free(node->blocks);
    free(node);
}

void cleanup() {
    freeTree(root);

    Block *temp = head;

    while (temp != NULL) {
        Block *next = temp->next;
        free(temp);
        temp = next;
    }

    free(disk);

    printf("Memory released successfully.\n");
}

int main() {
    char line[MAX];
    char command[20];
    char name[51];
    char content[MAX];

    if (!initialize()) {
        printf("Initialization failed.\n");
        cleanup();
        return 1;
    }

    printf("Virtual File System Started!\n");

    while (1) {
        pwd();
        printf("> ");

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        command[0] = '\0';
        name[0] = '\0';
        content[0] = '\0';

        sscanf(line, "%19s", command);

        if (strcmp(command, "exit") == 0) {
            break;
        }

        else if (strcmp(command, "mkdir") == 0) {
            sscanf(line, "%*s %50s", name);
            mkdir(name);
        }

        else if (strcmp(command, "create") == 0) {
            sscanf(line, "%*s %50s", name);
            createFile(name);
        }

        else if (strcmp(command, "write") == 0) {
            char *p = line + strlen(command);

            while (*p == ' ')
                p++;

            int i = 0;

            while (*p != ' ' && *p != '\0' && *p != '\n') {
                if (i < 50)
                    name[i++] = *p;
                p++;
            }

            name[i] = '\0';

            while (*p == ' ')
                p++;

            if (*p == '"') {
                p++;
                char *end = strrchr(p, '"');

                if (end != NULL)
                    *end = '\0';
            }
            else {
                p[strcspn(p, "\r\n")] = '\0';
            }

            strcpy(content, p);

            writeFile(name, content);
        }

        else if (strcmp(command, "read") == 0) {
            sscanf(line, "%*s %50s", name);
            readFile(name);
        }

        else if (strcmp(command, "delete") == 0) {
            sscanf(line, "%*s %50s", name);
            deleteFile(name);
        }

        else if (strcmp(command, "rmdir") == 0) {
            sscanf(line, "%*s %50s", name);
            rmdir(name);
        }

        else if (strcmp(command, "cd") == 0) {
            sscanf(line, "%*s %50s", name);
            cd(name);
        }

        else if (strcmp(command, "ls") == 0) {
            ls();
        }

        else if (strcmp(command, "pwd") == 0) {
            pwd();
        }

        else if (strcmp(command, "df") == 0) {
            df();
        }

        else {
            printf("Invalid command.\n");
        }
    }

    cleanup();

    printf("Exiting VFS...\n");

    return 0;
}
