#include <stdio.h>

#define MAX_BLOCKS 5
#define MAX_PROCESSES 5

// Memory blocks
int blocks[MAX_BLOCKS] = {100, 500, 200, 300, 600};
int process_size[MAX_PROCESSES] = {212, 417, 112, 426, 100};
int allocation[MAX_PROCESSES];  // Store which block each process got

// Initialize allocation array to -1 (not allocated)
void initialize() {
    for(int i = 0; i < MAX_PROCESSES; i++) {
        allocation[i] = -1;
    }
}

// Display current allocation status
void display() {
    printf("\nProcess\tSize\tBlock\n");
    for(int i = 0; i < MAX_PROCESSES; i++) {
        printf("P%d\t%d\t", i+1, process_size[i]);
        if(allocation[i] != -1)
            printf("%d (Size: %d)\n", allocation[i]+1, blocks[allocation[i]]);
        else
            printf("Not Allocated\n");
    }
}

// FIRST FIT: Allocate to first block that fits
void firstFit() {
    printf("\n=== FIRST FIT ALLOCATION ===\n");
    initialize();
    
    for(int i = 0; i < MAX_PROCESSES; i++) {
        for(int j = 0; j < MAX_BLOCKS; j++) {
            if(blocks[j] >= process_size[i]) {
                allocation[i] = j;  // Allocate to this block
                blocks[j] -= process_size[i];  // Reduce available space
                break;  // Found first fit, move to next process
            }
        }
    }
    display();
}

// BEST FIT: Allocate to smallest block that fits
void bestFit() {
    printf("\n=== BEST FIT ALLOCATION ===\n");
    initialize();
    int temp_blocks[MAX_BLOCKS] = {100, 500, 200, 300, 600};  // Copy original
    
    for(int i = 0; i < MAX_PROCESSES; i++) {
        int best_index = -1;
        // Find best block (smallest that fits)
        for(int j = 0; j < MAX_BLOCKS; j++) {
            if(temp_blocks[j] >= process_size[i]) {
                if(best_index == -1 || temp_blocks[j] < temp_blocks[best_index]) {
                    best_index = j;
                }
            }
        }
        
        if(best_index != -1) {
            allocation[i] = best_index;
            temp_blocks[best_index] -= process_size[i];
        }
    }
    display();
}

// WORST FIT: Allocate to largest block available
void worstFit() {
    printf("\n=== WORST FIT ALLOCATION ===\n");
    initialize();
    int temp_blocks[MAX_BLOCKS] = {100, 500, 200, 300, 600};  // Copy original
    
    for(int i = 0; i < MAX_PROCESSES; i++) {
        int worst_index = -1;
        // Find worst block (largest available)
        for(int j = 0; j < MAX_BLOCKS; j++) {
            if(temp_blocks[j] >= process_size[i]) {
                if(worst_index == -1 || temp_blocks[j] > temp_blocks[worst_index]) {
                    worst_index = j;
                }
            }
        }
        
        if(worst_index != -1) {
            allocation[i] = worst_index;
            temp_blocks[worst_index] -= process_size[i];
        }
    }
    display();
}

int main() {
    // Display initial memory blocks
    printf("Memory Blocks Available:\n");
    for(int i = 0; i < MAX_BLOCKS; i++) {
        printf("Block %d: %d KB\n", i+1, blocks[i]);
    }
    
    printf("\nProcess Sizes:\n");
    for(int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d: %d KB\n", i+1, process_size[i]);
    }
    
    // Test each strategy
    firstFit();
    
    // Reset blocks to original sizes
    int original_blocks[MAX_BLOCKS] = {100, 500, 200, 300, 600};
    for(int i = 0; i < MAX_BLOCKS; i++) {
        blocks[i] = original_blocks[i];
    }
    
    bestFit();
    
    // Reset again
    for(int i = 0; i < MAX_BLOCKS; i++) {
        blocks[i] = original_blocks[i];
    }
    
    worstFit();
    
    return 0;
}
