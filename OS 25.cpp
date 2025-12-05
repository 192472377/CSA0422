#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    int choice;
    printf("=== SIMPLE UNIX I/O DEMO ===\n");
    
    // Create a test file
    FILE *f = fopen("test.txt", "w");
    fprintf(f, "This is line 1\nThis is line 2\nThis is line 3\n");
    fclose(f);
    
    while(1) {
        printf("\n1. lseek() - File Seeking\n");
        printf("2. stat() - File Status\n");
        printf("3. Directory Listing\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if(choice == 1) {
            // lseek() demo
            printf("\n=== lseek() DEMO ===\n");
            
            int fd = open("test.txt", 0); // O_RDONLY = 0
            if(fd < 0) {
                printf("Error opening file!\n");
                continue;
            }
            
            // Read from position 5
            lseek(fd, 5, 0); // SEEK_SET = 0
            char buffer[100];
            int bytes = read(fd, buffer, 50);
            buffer[bytes] = '\0';
            printf("From position 5: %s\n", buffer);
            
            // Go back to start
            lseek(fd, 0, 0);
            bytes = read(fd, buffer, 10);
            buffer[bytes] = '\0';
            printf("First 10 chars: %s\n", buffer);
            
            close(fd);
            
        } else if(choice == 2) {
            // stat() demo
            printf("\n=== stat() DEMO ===\n");
            
            struct stat info;
            if(stat("test.txt", &info) == 0) {
                printf("File: test.txt\n");
                printf("Size: %ld bytes\n", info.st_size);
                printf("Permissions: %o\n", info.st_mode & 0777);
                
                // Check file type
                if((info.st_mode & S_IFMT) == S_IFREG)
                    printf("Type: Regular file\n");
                else if((info.st_mode & S_IFMT) == S_IFDIR)
                    printf("Type: Directory\n");
            } else {
                printf("Error getting file info!\n");
            }
            
        } else if(choice == 3) {
            // Directory listing
            printf("\n=== Directory Listing ===\n");
            
            DIR *dir = opendir(".");
            if(dir == NULL) {
                printf("Cannot open directory!\n");
                continue;
            }
            
            struct dirent *entry;
            printf("Files in current directory:\n");
            
            int count = 0;
            while((entry = readdir(dir)) != NULL) {
                if(entry->d_name[0] != '.') { // Skip hidden files
                    printf("  %s\n", entry->d_name);
                    count++;
                    if(count > 10) break;
                }
            }
            
            closedir(dir);
            printf("Total: %d files shown\n", count);
            
        } else if(choice == 4) {
            printf("Goodbye!\n");
            remove("test.txt");
            break;
            
        } else {
            printf("Invalid choice!\n");
        }
    }
    
    return 0;
}
