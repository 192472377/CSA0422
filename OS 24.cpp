#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

void create_file() {
    char filename[50];
    printf("Enter filename: ");
    scanf("%s", filename);
    
    int fd = creat(filename, 0644);
    if(fd < 0) {
        printf("Error creating file!\n");
    } else {
        printf("File '%s' created (fd=%d)\n", filename, fd);
        close(fd);
    }
}

void write_to_file() {
    char filename[50], text[200];
    printf("Enter filename: ");
    scanf("%s", filename);
    
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(fd < 0) {
        printf("Error opening file!\n");
        return;
    }
    
    printf("Enter text to write: ");
    getchar(); // Clear newline
    fgets(text, 200, stdin);
    
    write(fd, text, strlen(text));
    printf("Data written successfully\n");
    close(fd);
}

void read_file() {
    char filename[50], buffer[200];
    printf("Enter filename: ");
    scanf("%s", filename);
    
    int fd = open(filename, O_RDONLY);
    if(fd < 0) {
        printf("Error opening file!\n");
        return;
    }
    
    printf("\nFile contents:\n");
    printf("-------------\n");
    
    int bytes_read;
    while((bytes_read = read(fd, buffer, sizeof(buffer)-1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }
    printf("\n-------------\n");
    
    close(fd);
}

void file_info() {
    char filename[50];
    printf("Enter filename: ");
    scanf("%s", filename);
    
    struct stat info;
    if(stat(filename, &info) < 0) {
        printf("Error getting file info!\n");
        return;
    }
    
    printf("\nFile Information:\n");
    printf("Size: %ld bytes\n", info.st_size);
    printf("Permissions: %o\n", info.st_mode & 0777);
    printf("Last modified: %ld\n", info.st_mtime);
}

void delete_file() {
    char filename[50];
    printf("Enter filename to delete: ");
    scanf("%s", filename);
    
    if(unlink(filename) == 0) {
        printf("File '%s' deleted!\n", filename);
    } else {
        printf("Error deleting file!\n");
    }
}

int main() {
    int choice;
    
    printf("=== UNIX FILE MANAGEMENT ===\n");
    
    while(1) {
        printf("\n1. Create file\n");
        printf("2. Write to file\n");
        printf("3. Read file\n");
        printf("4. Get file info\n");
        printf("5. Delete file\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: create_file(); break;
            case 2: write_to_file(); break;
            case 3: read_file(); break;
            case 4: file_info(); break;
            case 5: delete_file(); break;
            case 6: printf("Goodbye!\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}
