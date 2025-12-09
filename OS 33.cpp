#include <stdio.h>

int main() {
    int frames[10], pages[30];
    int n, m, i, j, k, page_faults = 0;
    
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
    
    printf("\nOptimal Page Replacement:\n");
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
            } else {
                // Find page that will not be used for longest time in future
                int farthest = -1;
                int replace_index = 0;
                
                for(j = 0; j < n; j++) {
                    int next_use = m;  // Default to a large value
                    
                    // Find next use of this page in future
                    for(k = i + 1; k < m; k++) {
                        if(frames[j] == pages[k]) {
                            next_use = k;
                            break;
                        }
                    }
                    
                    // If this page won't be used again, or if it has farthest next use
                    if(next_use > farthest) {
                        farthest = next_use;
                        replace_index = j;
                    }
                }
                
                // Replace the optimal page
                frames[replace_index] = current_page;
            }
            
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
