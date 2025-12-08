#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];
    char search_text[100];
    char line[1000];
    int line_number = 0;
    int found_count = 0;
    
    printf("=== Simple GREP Command Simulator ===\n\n");
    
    // Get filename from user
    printf("Enter filename to search: ");
    scanf("%99s", filename);
    
    // Clear input buffer
    while(getchar() != '\n');
    
    // Get text to search
    printf("Enter text to search for: ");
    fgets(search_text, 100, stdin);
    
    // Remove newline character from search text
    search_text[strcspn(search_text, "\n")] = 0;
    
    printf("\n--- Searching for '%s' in '%s' ---\n\n", search_text, filename);
    
    // Step 1: Open the file
    file = fopen(filename, "r");
    
    // Check if file opened successfully
    if(file == NULL) {
        printf("Error: Cannot open file '%s'!\n", filename);
        printf("Make sure the file exists and you have permission to read it.\n");
        return 1;
    }
    
    // Step 2: Read file line by line
    while(fgets(line, 1000, file) != NULL) {
        line_number++;
        
        // Remove newline character from line for cleaner output
        line[strcspn(line, "\n")] = 0;
        
        // Step 3: Search for the text in this line
        if(strstr(line, search_text) != NULL) {
            printf("Line %d: %s\n", line_number, line);
            found_count++;
        }
    }
    
    // Step 4: Close the file
    fclose(file);
    
    // Step 5: Show results summary
    printf("\n--- Search Complete ---\n");
    if(found_count == 0) {
        printf("No matches found for '%s'\n", search_text);
    } else {
        printf("Found %d line(s) containing '%s'\n", found_count, search_text);
    }
    
    return 0;
}
