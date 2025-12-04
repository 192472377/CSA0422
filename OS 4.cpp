#include <stdio.h>

struct Process {
    int pid, bt, wt, tat;
};

int main() {
    int n = 4;
    struct Process p[] = {{1, 6, 0, 0}, {2, 8, 0, 0}, {3, 7, 0, 0}, {4, 3, 0, 0}};
    
    // Sort by burst time (SJF)
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(p[j].bt > p[j+1].bt) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
    
    // Calculate times
    for(int i = 1; i < n; i++)
        p[i].wt = p[i-1].wt + p[i-1].bt;
    
    for(int i = 0; i < n; i++)
        p[i].tat = p[i].wt + p[i].bt;
    
    // Display results
    printf("PID\tBurst\tWait\tTurnaround\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    
    return 0;
}
