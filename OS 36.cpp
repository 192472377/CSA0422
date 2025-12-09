#include <stdio.h>

int main() {
    int next[5];  // Next pointers: -1 means end
    int i, current;
    
    // Setup a simple linked file
    printf("Creating a linked file with 5 scattered blocks:\n\n");
    
    // Block numbers are scattered
    int blocks[5] = {3, 7, 2, 9, 5};
    
    // Setup links
    next[0] = 7;  // Block 3 -> Block 7
    next[1] = 2;  // Block 7 -> Block 2  
    next[2] = 9;  // Block 2 -> Block 9
    next[3] = 5;  // Block 9 -> Block 5
    next[4] = -1; // Block 5 -> END
    
    printf("File Structure:\n");
    printf("Directory: First=3, Last=5\n\n");
    printf("Block Chain: ");
    
    current = 3;  // Start from first block
    i = 0;
    while(current != -1) {
        printf("%d", current);
        if(next[i] != -1) {
            printf(" -> ");
        }
        current = next[i];
        i++;
    }
    
    printf("\n\n=== How to read file ===\n");
    printf("1. Look in directory: first block = 3\n");
    printf("2. Read block 3\n");
    printf("3. Block 3 says: next block = 7\n");
    printf("4. Read block 7\n");
    printf("5. Block 7 says: next block = 2\n");
    printf("6. Continue following pointers...\n");
    printf("7. Until you reach block with next = -1\n");
    
    printf("\n? Blocks can be anywhere on disk\n");
    printf("? Each block has data + pointer to next\n");
    printf("? Follow the chain to read entire file\n");
    
    return 0;
}
