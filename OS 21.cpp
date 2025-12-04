#include <stdio.h>

int main() {
    int memory[10] = {0};  // 10 memory blocks, 0 means free
    int processId = 1;
    int size, i, j;
    
    printf("WORST-FIT MEMORY ALLOCATION\n");
    printf("Memory has 10 blocks (0-9)\n");
    printf("0 = Free, Other numbers = Process ID\n\n");
    
    while (1) {
        // Show current memory
        printf("Current Memory: ");
        for (i = 0; i < 10; i++) {
            if (memory[i] == 0)
                printf("[ ]");
            else
                printf("[P%d]", memory[i]);
        }
        printf("\n");
        
        printf("\nOptions:\n");
        printf("1. Allocate memory\n");
        printf("2. Free memory\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        
        int choice;
        scanf("%d", &choice);
        
        if (choice == 3) break;
        
        if (choice == 1) {
            printf("Enter size needed (1-10): ");
            scanf("%d", &size);
            
            // Find largest free space (worst fit)
            int max_size = 0, max_start = -1;
            int current_size = 0, current_start = -1;
            
            for (i = 0; i < 10; i++) {
                if (memory[i] == 0) {
                    if (current_size == 0) {
                        current_start = i;
                    }
                    current_size++;
                } else {
                    if (current_size > max_size) {
                        max_size = current_size;
                        max_start = current_start;
                    }
                    current_size = 0;
                }
            }
            
            // Check last block
            if (current_size > max_size) {
                max_size = current_size;
                max_start = current_start;
            }
            
            printf("Largest free space: %d blocks\n", max_size);
            
            if (max_size >= size) {
                // Allocate
                for (i = max_start; i < max_start + size; i++) {
                    memory[i] = processId;
                }
                printf("Allocated blocks %d-%d to Process P%d\n\n", 
                       max_start, max_start+size-1, processId);
                processId++;
            } else {
                printf("Cannot allocate! Not enough space.\n\n");
            }
        }
        else if (choice == 2) {
            printf("Enter Process ID to free: ");
            int freeId;
            scanf("%d", &freeId);
            
            for (i = 0; i < 10; i++) {
                if (memory[i] == freeId) {
                    memory[i] = 0;
                }
            }
            printf("Memory freed for Process P%d\n\n", freeId);
        }
    }
    
    printf("\nProgram ended. Press any key to exit...");
    getchar();
    getchar();
    
    return 0;
}

