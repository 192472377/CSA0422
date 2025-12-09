#include <stdio.h>

int main() {
    int frames[10], pages[20];
    int n, m, i, j, k, page_faults = 0, oldest = 0;
    
    printf("Enter number of frames: ");
    scanf("%d", &n);
    
    printf("Enter number of pages: ");
    scanf("%d", &m);
    
    printf("Enter page reference string: ");
    for(i = 0; i < m; i++) {
        scanf("%d", &pages[i]);
    }
    
    // Initialize all frames to -1 (empty)
    for(i = 0; i < n; i++) {
        frames[i] = -1;
    }
    
    printf("\nFIFO Page Replacement:\n");
    printf("Page\tFrames\t\tFault\n");
    printf("----\t------\t\t-----\n");
    
    for(i = 0; i < m; i++) {
        int current_page = pages[i];
        int found = 0;
        
        // Check if page is already in frames
        for(j = 0; j < n; j++) {
            if(frames[j] == current_page) {
                found = 1;
                break;
            }
        }
        
        // If page not found, it's a page fault
        if(!found) {
            frames[oldest] = current_page;
            oldest = (oldest + 1) % n;  // Move to next frame (circular)
            page_faults++;
            
            // Display with fault
            printf("%d\t", current_page);
            for(k = 0; k < n; k++) {
                if(frames[k] == -1)
                    printf("[ ] ");
                else
                    printf("[%d] ", frames[k]);
            }
            printf("\tFault\n");
        } else {
            // Display without fault
            printf("%d\t", current_page);
            for(k = 0; k < n; k++) {
                if(frames[k] == -1)
                    printf("[ ] ");
                else
                    printf("[%d] ", frames[k]);
            }
            printf("\tHit\n");
        }
    }
    
    printf("\nTotal Page Faults: %d\n", page_faults);
    
    return 0;
}
