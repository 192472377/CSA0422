#include <stdio.h>

int main() {
    int index_block[10];  // Index block stores pointers to data blocks
    int data_blocks[10];  // Data blocks (simplified)
    int n, i, block_num;
    
    printf("Enter number of blocks in file: ");
    scanf("%d", &n);
    
    // Setup index block
    printf("\n=== SETTING UP INDEXED FILE ===\n");
    printf("Creating index block with %d entries:\n", n);
    
    for(i = 0; i < n; i++) {
        index_block[i] = 100 + i;  // Pointers to physical blocks
        data_blocks[i] = (i + 1) * 10;  // Sample data
        printf("  Index[%d] -> Block %d (Data: %d)\n", 
               i, index_block[i], data_blocks[i]);
    }
    
    printf("\nFile created! Index block ready.\n");
    printf("To access any block:\n");
    printf("1. Go to index block\n");
    printf("2. Read pointer at position i\n");
    printf("3. Jump directly to that block\n");
    
    printf("\n=== DEMONSTRATION ===\n");
    
    // Demonstrate accessing different blocks
    printf("\nLet's access block 3:\n");
    printf("1. Go to index block\n");
    printf("2. Read Index[3] = %d\n", index_block[3]);
    printf("3. Jump to block %d\n", index_block[3]);
    printf("4. Read data: %d\n", data_blocks[3]);
    
    printf("\nLet's access block 0:\n");
    printf("1. Go to index block\n");
    printf("2. Read Index[0] = %d\n", index_block[0]);
    printf("3. Jump to block %d\n", index_block[0]);
    printf("4. Read data: %d\n", data_blocks[0]);
    
    // Interactive demo
    while(1) {
        printf("\nEnter block number to access (0-%d, -1 to exit): ", n-1);
        scanf("%d", &block_num);
        
        if(block_num == -1) {
            break;
        }
        
        if(block_num < 0 || block_num >= n) {
            printf("Invalid block number!\n");
            continue;
        }
        
        printf("\nAccessing Block %d:\n", block_num);
        printf("1. Look at Index[%d] = %d\n", block_num, index_block[block_num]);
        printf("2. Go directly to Block %d\n", index_block[block_num]);
        printf("3. Data = %d\n", data_blocks[block_num]);
        
        printf("\n? Direct access achieved!\n");
        printf("? No need to read blocks 0 to %d\n", block_num-1);
    }
    
    printf("\n=== SUMMARY ===\n");
    printf("Indexed Allocation Advantages:\n");
    printf("1. Direct access to any block\n");
    printf("2. No need to read previous blocks\n");
    printf("3. Random access is fast\n");
    
    return 0;
}
