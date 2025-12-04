#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY 10

int memory[MAX_MEMORY] = {0};  // 0 means free

// Display memory
void displayMemory() {
    printf("\nMemory Status:\n");
    printf("Index:  ");
    for (int i = 0; i < MAX_MEMORY; i++) {
        printf("%2d ", i);
    }
    printf("\nStatus: ");
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == 0)
            printf(" . ");
        else
            printf("P%d ", memory[i]);
    }
    printf("\n");
}

// First-fit allocation
void allocateFirstFit(int processId, int size) {
    printf("\nProcess P%d requesting %d blocks...\n", processId, size);
    
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == 0) {
            // Found free block, check if enough space
            int free_space = 0;
            for (int j = i; j < MAX_MEMORY && memory[j] == 0; j++) {
                free_space++;
                if (free_space >= size) break;
            }
            
            if (free_space >= size) {
                // Allocate memory
                for (int j = i; j < i + size; j++) {
                    memory[j] = processId;
                }
                printf("? SUCCESS: Allocated blocks [%d-%d] to Process P%d\n", 
                       i, i + size - 1, processId);
                return;
            }
        }
    }
    
    printf("? FAILED: Not enough contiguous memory for Process P%d\n", processId);
}

// Free memory
void freeMemory(int processId) {
    printf("\nFreeing memory for Process P%d...\n", processId);
    int freed = 0;
    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == processId) {
            memory[i] = 0;
            freed = 1;
        }
    }
    if (freed)
        printf("? Memory freed successfully!\n");
    else
        printf("? Process P%d not found!\n", processId);
}

int main() {
    printf("========================================\n");
    printf("      FIRST-FIT MEMORY ALLOCATION\n");
    printf("========================================\n");
    printf("Total Memory: %d blocks\n\n", MAX_MEMORY);
    
    displayMemory();
    
    // Demonstrate First-Fit
    printf("\n--- FIRST-FIT DEMONSTRATION ---\n");
    
    // Allocate some processes
    allocateFirstFit(1, 2);
    displayMemory();
    
    allocateFirstFit(2, 3);
    displayMemory();
    
    allocateFirstFit(3, 1);
    displayMemory();
    
    freeMemory(1);
    displayMemory();
    
    // New request - should use first available space
    printf("\nNew request - Process P4 needs 2 blocks\n");
    printf("First-Fit will use first available space (blocks 0-1)\n");
    allocateFirstFit(4, 2);
    displayMemory();
    
    printf("\n========================================\n");
    printf("       FIRST-FIT EXPLANATION\n");
    printf("========================================\n");
    printf("First-Fit algorithm:\n");
    printf("1. Start from beginning of memory\n");
    printf("2. Find FIRST free block that can fit the request\n");
    printf("3. Allocate immediately\n");
    printf("4. Don't search for better fit\n\n");
    
    printf("Advantages:\n");
    printf("- Fast (stops at first suitable block)\n");
    printf("- Simple to implement\n\n");
    
    printf("Disadvantages:\n");
    printf("- Can cause fragmentation at beginning\n");
    printf("- May not use memory optimally\n");
    
    printf("\nPress any key to exit...");
    system("pause");
    return 0;
}
