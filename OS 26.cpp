#include <stdio.h>

int main() {
    FILE *file;
    char filename[100];
    char text[1000];
    int choice;
    
    printf("=== Simple File Manager ===\n");
    
    do {
        printf("\n--- Menu ---\n");
        printf("1. Create and Write to a file\n");
        printf("2. Read from a file\n");
        printf("3. Append text to a file\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        // Clear input buffer
        while(getchar() != '\n');
        
        switch(choice) {
            case 1: // Create and Write
                printf("\nEnter filename: ");
                scanf("%99s", filename);
                
                file = fopen(filename, "w"); // 'w' for write mode
                
                if(file == NULL) {
                    printf("Error creating file!\n");
                    break;
                }
                
                printf("Enter text to write (max 1000 chars):\n");
                while(getchar() != '\n'); // Clear buffer
                fgets(text, 1000, stdin);
                
                fputs(text, file);
                fclose(file);
                printf("File created and written successfully!\n");
                break;
                
            case 2: // Read
                printf("\nEnter filename to read: ");
                scanf("%99s", filename);
                
                file = fopen(filename, "r"); // 'r' for read mode
                
                if(file == NULL) {
                    printf("Error: File not found!\n");
                    break;
                }
                
                printf("\n--- File Content ---\n");
                while(fgets(text, 1000, file) != NULL) {
                    printf("%s", text);
                }
                printf("--- End of File ---\n");
                
                fclose(file);
                break;
                
            case 3: // Append
                printf("\nEnter filename: ");
                scanf("%99s", filename);
                
                file = fopen(filename, "a"); // 'a' for append mode
                
                if(file == NULL) {
                    printf("Error: File not found!\n");
                    break;
                }
                
                printf("Enter text to append:\n");
                while(getchar() != '\n'); // Clear buffer
                fgets(text, 1000, stdin);
                
                fputs(text, file);
                fclose(file);
                printf("Text appended successfully!\n");
                break;
                
            case 4:
                printf("\nGoodbye!\n");
                break;
                
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 4);
    
    return 0;
}
