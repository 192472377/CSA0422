#include <stdio.h>

struct Process {
    int pid, bt, at, wt, tat, ct;
};

int main() {
    int n = 4;
    struct Process p[] = {
        {1, 6, 0, 0, 0, 0},
        {2, 8, 1, 0, 0, 0},
        {3, 7, 2, 0, 0, 0},
        {4, 3, 3, 0, 0, 0}
    };
    
    int completed = 0, time = 0;
    
    printf("Non-preemptive SJF with Arrival Time\n");
    
    while(completed < n) {
        int idx = -1;
        int min_bt = 9999;
        
        // Find shortest job that has arrived
        for(int i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].ct == 0 && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }
        
        if(idx != -1) {
            // Execute the process to completion (non-preemptive)
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            completed++;
            printf("Executed P%d from %d to %d\n", p[idx].pid, time-p[idx].bt, time);
        } else {
            time++;
        }
    }
    
    // Display results
    printf("\nPID\tArrival\tBurst\tWait\tTurnaround\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    
    return 0;
}
