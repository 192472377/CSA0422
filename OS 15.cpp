#include <stdio.h>
#include <string.h>

struct File {
    char name[20];
    int size;
};

struct Directory {
    char name[20];
    struct File files[10];
    int file_count;
};

struct Directory dirs[10];
int dir_count = 0;

void create_dir() {
    if(dir_count >= 10) {
        printf("Max directories reached!\n");
        return;
    }
    
    printf("Enter directory name: ");
    scanf("%s", dirs[dir_count].name);
    dirs[dir_count].file_count = 0;
    dir_count++;
    printf("Directory created!\n");
}

void create_file() {
    if(dir_count == 0) {
        printf("No directories exist! Create one first.\n");
        return;
    }
    
    char dir_name[20];
    printf("Enter directory name: ");
    scanf("%s", dir_name);
    
    for(int i = 0; i < dir_count; i++) {
        if(strcmp(dirs[i].name, dir_name) == 0) {
            if(dirs[i].file_count >= 10) {
                printf("Directory full!\n");
                return;
            }
            
            printf("Enter filename: ");
            scanf("%s", dirs[i].files[dirs[i].file_count].name);
            printf("Enter file size: ");
            scanf("%d", &dirs[i].files[dirs[i].file_count].size);
            dirs[i].file_count++;
            printf("File created!\n");
            return;
        }
    }
    printf("Directory not found!\n");
}

void display_all() {
    printf("\nTwo-Level Directory Structure:\n");
    for(int i = 0; i < dir_count; i++) {
        printf("\nDirectory: %s\n", dirs[i].name);
        if(dirs[i].file_count == 0) {
            printf("  (Empty)\n");
        } else {
            printf("  Files:\n");
            printf("  Name\tSize\n");
            for(int j = 0; j < dirs[i].file_count; j++) {
                printf("  %s\t%d\n", dirs[i].files[j].name, dirs[i].files[j].size);
            }
        }
    }
}

void search_file() {
    char filename[20];
    printf("Enter filename to search: ");
    scanf("%s", filename);
    
    for(int i = 0; i < dir_count; i++) {
        for(int j = 0; j < dirs[i].file_count; j++) {
            if(strcmp(dirs[i].files[j].name, filename) == 0) {
                printf("File found in directory: %s\n", dirs[i].name);
                printf("Size: %d\n", dirs[i].files[j].size);
                return;
            }
        }
    }
    printf("File not found!\n");
}

int main() {
    int choice;
    
    // Create some default directories and files
    strcpy(dirs[0].name, "Documents");
    dirs[0].file_count = 2;
    strcpy(dirs[0].files[0].name, "notes.txt");
    dirs[0].files[0].size = 100;
    strcpy(dirs[0].files[1].name, "report.pdf");
    dirs[0].files[1].size = 500;
    
    strcpy(dirs[1].name, "Images");
    dirs[1].file_count = 1;
    strcpy(dirs[1].files[0].name, "photo.jpg");
    dirs[1].files[0].size = 1000;
    
    dir_count = 2;
    
    while(1) {
        printf("\n1. Create directory\n2. Create file\n3. Display all\n4. Search file\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: create_dir(); break;
            case 2: create_file(); break;
            case 3: display_all(); break;
            case 4: search_file(); break;
            case 5: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
