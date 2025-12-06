#include <stdio.h>

int main() {

    int processes[5][3] = {
        {1, 10, 3}, 
        {2, 5, 1},   
        {3, 8, 4},   
        {4, 4, 2},   
        {5, 6, 5}    
    };
    
    int n = 5;
   
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(processes[j][2] > processes[j+1][2]) { 
                int temp[3];
                temp[0] = processes[j][0];
                temp[1] = processes[j][1];
                temp[2] = processes[j][2];
                
                processes[j][0] = processes[j+1][0];
                processes[j][1] = processes[j+1][1];
                processes[j][2] = processes[j+1][2];
                
                processes[j+1][0] = temp[0];
                processes[j+1][1] = temp[1];
                processes[j+1][2] = temp[2];
            }
        }
    }

    printf("Execution Order (by Priority):\n");
    printf("Process\tBurst Time\tPriority\n");
    
    int wait = 0;
    int total_wait = 0;
    
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\n", 
               processes[i][0], 
               processes[i][1], 
               processes[i][2]);
        
        if(i > 0) {
            wait += processes[i-1][1];
            total_wait += wait;
        }
    }
    
    printf("\nAverage Waiting Time: %.2f\n", (float)total_wait / n);
    
    return 0;
}
