#include <stdio.h>

int main() {
    int n, m;  // n = processes, m = resources
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    
    int max[n][m];      // Maximum need
    int alloc[n][m];    // Currently allocated
    int need[n][m];     // Remaining need
    int avail[m];       // Available resources
    int finish[n];      // Track finished processes
    
    // Initialize finish array to 0
    for(int i = 0; i < n; i++) {
        finish[i] = 0;
    }
    
    // Input Allocation matrix
    printf("\nEnter Allocation matrix:\n");
    for(int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    
    // Input Max matrix
    printf("\nEnter Max matrix:\n");
    for(int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    // Input Available resources
    printf("\nEnter Available resources: ");
    for(int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }
    
    // Calculate Need matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    // Display matrices
    printf("\n=== Current State ===\n");
    printf("Process\tAlloc\tMax\tNeed\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t", i);
        for(int j = 0; j < m; j++) printf("%d ", alloc[i][j]);
        printf("\t");
        for(int j = 0; j < m; j++) printf("%d ", max[i][j]);
        printf("\t");
        for(int j = 0; j < m; j++) printf("%d ", need[i][j]);
        printf("\n");
    }
    
    printf("\nAvailable: ");
    for(int j = 0; j < m; j++) printf("%d ", avail[j]);
    printf("\n");
    
    // Banker's Algorithm
    int safe_seq[n];
    int count = 0;
    
    printf("\n=== Banker's Algorithm Execution ===\n");
    
    while(count < n) {
        int found = 0;
        
        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int can_execute = 1;
                
                // Check if need <= available
                for(int j = 0; j < m; j++) {
                    if(need[i][j] > avail[j]) {
                        can_execute = 0;
                        break;
                    }
                }
                
                if(can_execute) {
                    // Process can execute
                    printf("\nProcess P%d can execute.\n", i);
                    printf("Resources allocated to P%d: ", i);
                    for(int j = 0; j < m; j++) printf("%d ", alloc[i][j]);
                    
                    // Release resources
                    for(int j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                    }
                    
                    printf("\nResources released. New available: ");
                    for(int j = 0; j < m; j++) printf("%d ", avail[j]);
                    
                    finish[i] = 1;
                    safe_seq[count] = i;
                    count++;
                    found = 1;
                    break;
                }
            }
        }
        
        if(!found) {
            printf("\nNo process can execute! System is in UNSAFE state.\n");
            break;
        }
    }
    
    // Check if all processes finished
    if(count == n) {
        printf("\n\nSystem is in SAFE state!\n");
        printf("Safe sequence: ");
        for(int i = 0; i < n; i++) {
            printf("P%d ", safe_seq[i]);
        }
        printf("\n");
    } else {
        printf("\nDeadlock detected! System is UNSAFE.\n");
    }
    
    return 0;
}
