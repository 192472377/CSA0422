#include <stdio.h>
#include <dirent.h>  // For reading directories
#include <stdlib.h>  // For exit()

int main() {
    DIR *folder;  // Pointer to directory
    struct dirent *file;  // Pointer to file entry
    
    printf("=== Simple ls Command ===\n");
    printf("Listing files in current folder:\n\n");
    
    // Step 1: Open the current directory
    folder = opendir(".");
    
    // Check if directory opened successfully
    if(folder == NULL) {
        printf("Error: Cannot open current folder!\n");
        exit(1);  // Exit program with error
    }
    
    // Step 2: Read and print each file name
    int count = 1;
    while((file = readdir(folder)) != NULL) {
        // Skip hidden files (those starting with .)
        if(file->d_name[0] != '.') {
            printf("%2d. %s\n", count, file->d_name);
            count++;
        }
    }
    
    printf("\nTotal: %d files/folders found\n", count-1);
    
    // Step 3: Close the directory
    closedir(folder);
    
    return 0;
}
