#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr1, *fptr2;
    char filename[100];
    int c;  // Changed from char to int to properly handle EOF
    
    printf("Enter the filename to open for reading: ");
    scanf("%99s", filename);  // Added buffer limit
    
    fptr1 = fopen(filename, "r");
    if (fptr1 == NULL) {
        printf("Cannot open file %s for reading\n", filename);
        system("pause");
        exit(0);
    }
    
    printf("Enter the filename to open for writing: ");
    scanf("%99s", filename);  // Added buffer limit
    
    fptr2 = fopen(filename, "w");
    if (fptr2 == NULL) {
        printf("Cannot open file %s for writing\n", filename);
        fclose(fptr1);  // Close the first file before exiting
        system("pause");
        exit(0);
    }
    
    // Copy contents
    while ((c = fgetc(fptr1)) != EOF) {
        fputc(c, fptr2);
    }
    
    printf("\nContents copied to %s\n", filename);
    
    fclose(fptr1);
    fclose(fptr2);
    
    system("pause");  // Keep console window open in DEV C++
    return 0;
}

