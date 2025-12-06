#include <stdio.h>

int main() {
    int n, head, i, j, temp, seek = 0;
    
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    
    int req[n];
    
    printf("Enter disk requests: ");
    for(i = 0; i < n; i++)
        scanf("%d", &req[i]);
    
    printf("Enter initial head position: ");
    scanf("%d", &head);
    
    printf("Enter direction (0 for left, 1 for right): ");
    int direction;
    scanf("%d", &direction);
    
    // Sort requests in ascending order
    for(i = 0; i < n-1; i++) {
        for(j = 0; j < n-i-1; j++) {
            if(req[j] > req[j+1]) {
                temp = req[j];
                req[j] = req[j+1];
                req[j+1] = temp;
            }
        }
    }
    
    printf("\nSorted requests: ");
    for(i = 0; i < n; i++)
        printf("%d ", req[i]);
    
    // Find position of head in sorted array
    int pos;
    for(i = 0; i < n; i++) {
        if(req[i] > head) {
            pos = i;
            break;
        }
    }
    
    printf("\n\nSeek Sequence: %d", head);
    
    if(direction == 0) { // Moving left first
        // Move left from head to start
        for(i = pos-1; i >= 0; i--) {
            seek += head - req[i];
            head = req[i];
            printf(" -> %d", head);
        }
        
        // Move to 0 (left boundary)
        if(head != 0) {
            seek += head;
            head = 0;
            printf(" -> %d", head);
        }
        
        // Now move right
        for(i = pos; i < n; i++) {
            seek += req[i] - head;
            head = req[i];
            printf(" -> %d", head);
        }
    }
    else { // Moving right first
        // Move right from head to end
        for(i = pos; i < n; i++) {
            seek += req[i] - head;
            head = req[i];
            printf(" -> %d", head);
        }
        
        // Move to 199 (right boundary - assuming disk size 200)
        if(head != 199) {
            seek += 199 - head;
            head = 199;
            printf(" -> %d", head);
        }
        
        // Now move left
        for(i = pos-1; i >= 0; i--) {
            seek += head - req[i];
            head = req[i];
            printf(" -> %d", head);
        }
    }
    
    printf("\n\nTotal Seek Operations: %d", seek);
    printf("\nAverage Seek Time: %.2f\n", (float)seek/n);
    
    return 0;
}
