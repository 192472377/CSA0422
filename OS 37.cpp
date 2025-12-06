#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, total_movement = 0;
    
    printf("=== FCFS Disk Scheduling Algorithm ===\n\n");
    
    // Input: Number of disk requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);
    
    // Create array to store disk requests
    int requests[n];
    
    // Input: Disk requests
    printf("\nEnter the disk requests (one by one):\n");
    for(int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }
    
    // Input: Initial head position
    printf("\nEnter the initial head position: ");
    scanf("%d", &head);
    
    printf("\n=== FCFS Disk Scheduling Process ===\n");
    printf("Initial Head Position: %d\n", head);
    printf("\nOrder of service:\n");
    printf("%d", head);
    
    // Calculate total head movement
    for(int i = 0; i < n; i++) {
        // Calculate movement from current head to next request
        int movement = abs(head - requests[i]);
        total_movement += movement;
        
        printf(" -> %d", requests[i]);
        
        // Update head position to current request
        head = requests[i];
    }
    
    printf("\n\nTotal Head Movement: %d cylinders\n", total_movement);
    printf("Average Head Movement: %.2f cylinders\n", (float)total_movement / n);
    
    return 0;
}
