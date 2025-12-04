#include <stdio.h>

struct Process {
    int pid, bt, priority, wt, tat;
};

int main() {
    int n = 5;
    struct Process p[] = {
        {1, 10, 3, 0, 0},
        {2, 1, 1, 0, 0},
        {3, 2, 4, 0, 0},
        {4, 1, 5, 0, 0},
        {5, 5, 2, 0, 0}
    };
    
    // Sort by priority (higher number = higher priority)
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(p[j].priority < p[j+1].priority) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
    
    // Calculate waiting and turnaround times
    for(int i = 1; i < n; i++)
        p[i].wt = p[i-1].wt + p[i-1].bt;
    
    for(int i = 0; i < n; i++)
        p[i].tat = p[i].wt + p[i].bt;
    
    // Display results
    printf("Priority Scheduling (Higher number = Higher priority)\n");
    printf("PID\tBurst\tPriority\tWait\tTurnaround\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t\t%d\t%d\n", p[i].pid, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    
    return 0;
}
