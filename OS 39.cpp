#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, size, dir;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n];
    printf("Enter requests: ");
    for(int i=0;i<n;i++) scanf("%d", &req[i]);

    printf("Enter head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &size);

    printf("Direction (1=right, 0=left): ");
    scanf("%d", &dir);

    // Sort requests
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(req[j] > req[j+1]) {
                int t=req[j]; req[j]=req[j+1]; req[j+1]=t;
            }

    int total = 0;
    int pos = 0;

    // Find where head fits in sorted order
    for(int i=0;i<n;i++)
        if(req[i] >= head) { pos = i; break; }

    printf("\nOrder: %d -> ", head);

    if(dir == 1) {
        // Move right side first
        for(int i=pos;i<n;i++) {
            total += abs(req[i] - head);
            head = req[i];
            printf("%d -> ", head);
        }

        // Go to end of disk
        total += (size - 1 - head);
        printf("%d -> ", size-1);

        // Jump to 0 (counting jump)
        total += (size - 1);
        head = 0;
        printf("0 -> ");

        // Now serve left side
        for(int i=0;i<pos;i++) {
            total += abs(req[i] - head);
            head = req[i];
            printf("%d -> ", head);
        }
    }

    else { // dir = 0 (left)
        // Move left side first
        for(int i=pos-1;i>=0;i--) {
            total += abs(req[i] - head);
            head = req[i];
            printf("%d -> ", head);
        }

        // Go to start
        total += head;
        printf("0 -> ");

        // Jump to end
        total += (size - 1);
        head = size - 1;
        printf("%d -> ", head);

        // Serve right side
        for(int i=n-1;i>=pos;i--) {
            total += abs(req[i] - head);
            head = req[i];
            printf("%d -> ", head);
        }
    }

    printf("\nTotal Seek Time = %d\n", total);
    return 0;
}
