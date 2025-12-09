#include <stdio.h>

int main() {
    int frames[10], pages[20], counter[20];
    int n, m, i, j, k, page_faults = 0, min, pos;
    
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
    
    printf("\nLRU Page Replacement:\n");
    printf("Page\tFrames\t\tFault\tCounter\n");
    printf("----\t------\t\t-----\t-------\n");
    
    // Counter to track usage time
    int time = 0;
    
    for(i = 0; i < m; i++) {
        int current_page = pages[i];
        int found = 0;
        
        // Check if page is already in frames
        for(j = 0; j < n; j++) {
            if(frames[j] == current_page) {
                found = 1;
                counter[j] = time;  // Update usage time
                time++;
                break;
            }
        }
        
        // If page not found, it's a page fault
        if(!found) {
            // Find empty frame first
            int empty_frame = -1;
            for(j = 0; j < n; j++) {
                if(frames[j] == -1) {
                    empty_frame = j;
                    break;
                }
            }
            
            if(empty_frame != -1) {
                // There's an empty frame
                frames[empty_frame] = current_page;
                counter[empty_frame] = time;
            } else {
                // Find least recently used frame (smallest counter value)
                min = counter[0];
                pos = 0;
                for(j = 1; j < n; j++) {
                    if(counter[j] < min) {
                        min = counter[j];
                        pos = j;
                    }
                }
                // Replace the LRU page
                frames[pos] = current_page;
                counter[pos] = time;
            }
            
            time++;
            page_faults++;
            
            // Display with fault
            printf("%d\t", current_page);
            for(k = 0; k < n; k++) {
                if(frames[k] == -1)
                    printf("[ ] ");
                else
                    printf("[%d] ", frames[k]);
            }
            printf("\tFault\t");
            for(k = 0; k < n; k++) {
                if(frames[k] != -1)
                    printf("%d ", counter[k]);
            }
            printf("\n");
        } else {
            // Display without fault
            printf("%d\t", current_page);
            for(k = 0; k < n; k++) {
                if(frames[k] == -1)
                    printf("[ ] ");
                else
                    printf("[%d] ", frames[k]);
            }
            printf("\tHit\t");
            for(k = 0; k < n; k++) {
                if(frames[k] != -1)
                    printf("%d ", counter[k]);
            }
            printf("\n");
        }
    }
    
    printf("\nTotal Page Faults: %d\n", page_faults);
    
    return 0;
}
