#include <stdio.h>
#include <string.h>

struct File {
    char name[20];
    int size;
};

struct File dir[100];
int file_count = 0;

void create_file() {
    if(file_count >= 100) {
        printf("Directory full!\n");
        return;
    }
    
    printf("Enter filename: ");
    scanf("%s", dir[file_count].name);
    printf("Enter file size: ");
    scanf("%d", &dir[file_count].size);
    
    file_count++;
    printf("File created!\n");
}

void delete_file() {
    char name[20];
    printf("Enter filename to delete: ");
    scanf("%s", name);
    
    for(int i = 0; i < file_count; i++) {
        if(strcmp(dir[i].name, name) == 0) {
            for(int j = i; j < file_count-1; j++) {
                dir[j] = dir[j+1];
            }
            file_count--;
            printf("File deleted!\n");
            return;
        }
    }
    printf("File not found!\n");
}

void display_files() {
    printf("\nDirectory Contents:\n");
    printf("Name\tSize\n");
    for(int i = 0; i < file_count; i++) {
        printf("%s\t%d\n", dir[i].name, dir[i].size);
    }
}

int main() {
    int choice;
    
    while(1) {
        printf("\n1. Create file\n2. Delete file\n3. Display files\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: create_file(); break;
            case 2: delete_file(); break;
            case 3: display_files(); break;
            case 4: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
