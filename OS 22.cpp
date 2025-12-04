#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10  // Total memory blocks

int memory[MAX_SIZE] = {0};  // 0 means free

// Display memory status
void displayMemory() {
    printf("\nMemory Blocks:\n");
    printf("Index:  ");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%2d ", i);
    }
    
    printf("\nStatus: ");
    for (int i = 0; i < MAX_SIZE; i++) {
        if (memory[i] == 0) {
            printf(" . ");
        } else {
            printf("P%d ", memory[i]);
        }
    }
    printf("\n");
}

// Best-fit allocation
void allocateMemory(int processId, int size) {
    printf("\nProcess P%d requesting %d blocks...\n", processId, size);
    
    int best_start = -1;
    int best_size = MAX_SIZE + 1;  // Start with a large value
    int current_start = -1;
    int current_size = 0;
    
    // Find all free blocks and choose the best fit (smallest sufficient block)
    for (int i = 0; i < MAX_SIZE; i++) {
        if (memory[i] == 0) {
            if (current_size == 0) {
                current_start = i;
            }
            current_size++;
        }
        
        // When we hit allocated memory or end of memory
        if (memory[i] != 0 || i == MAX_SIZE - 1) {
            if (current_size >= size && current_size < best_size) {
                best_size = current_size;
                best_start = current_start;
            }
            current_size = 0;
        }
    }
    
    if (best_start != -1) {
        // Allocate memory
        for (int i = best_start; i < best_start + size; i++) {
            memory[i] = processId;
        }
        printf("? SUCCESS: Allocated blocks [%d-%d] to Process P%d\n", 
               best_start, best_start + size - 1, processId);
        printf("  Best fit block size: %d (wasted: %d blocks)\n", 
               best_size, best_size - size);
    } else {
        printf("? FAILED: No suitable block found for Process P%d\n", processId);
    }
}

// Free memory for a process
void freeMemory(int processId) {
    int freed = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (memory[i] == processId) {
            memory[i] = 0;
            freed++;
        }
    }
    if (freed > 0) {
        printf("\n? Freed %d blocks from Process P%d\n", freed, processId);
    } else {
        printf("\n? Process P%d not found in memory\n", processId);
    }
}

int main() {
    printf("========================================\n");
    printf("      BEST-FIT MEMORY ALLOCATION\n");
    printf("========================================\n");
    printf("Total Memory: %d blocks\n", MAX_SIZE);
    printf(". = Free memory\n");
    printf("P1,P2,... = Process using memory\n");
    
    displayMemory();
    
    // Demonstration
    printf("\n--- DEMONSTRATION ---\n");
    
    allocateMemory(1, 3);
    displayMemory();
    
    allocateMemory(2, 2);
    displayMemory();
    
    allocateMemory(3, 4);
    displayMemory();
    
    freeMemory(1);
    displayMemory();
    
    allocateMemory(4, 2);  // Should use the freed 3-block space
    displayMemory();
    
    printf("\n--- TESTING BEST-FIT ---\n");
    
    // Clear memory for new test
    for (int i = 0; i < MAX_SIZE; i++) memory[i] = 0;
    displayMemory();
    
    // Create fragmented memory: P1(2), Free(1), P2(2), Free(3), P3(1), Free(1)
    printf("\nCreating fragmented memory...\n");
    memory[0] = memory[1] = 1;      // P1: 2 blocks
    memory[3] = memory[4] = 2;      // P2: 2 blocks
    memory[8] = 3;                  // P3: 1 block
    
    displayMemory();
    
    printf("\nRequesting 2 blocks...\n");
    printf("Available free blocks: size 1, size 3, size 1\n");
    printf("Best fit will choose size 3 block (index 5-7)\n");
    
    allocateMemory(4, 2);  // Should choose the 3-block space
    displayMemory();
    
    printf("\n========================================\n");
    printf("           BEST-FIT EXPLANATION\n");
    printf("========================================\n");
    printf("Best-Fit algorithm:\n");
    printf("1. Finds ALL free memory blocks\n");
    printf("2. Chooses the SMALLEST block that is BIG ENOUGH\n");
    printf("3. This minimizes wasted space\n");
    printf("4. But can cause external fragmentation\n");
    
    printf("\nPress any key to exit...");
    system("pause");
    
    return 0;
}
