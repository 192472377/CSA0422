#include <stdio.h>

struct Process {
    int pid, bt, rt, wt, tat;
};

int main() {
    int n, tq;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &tq);
    
    struct Process p[n];
    
    // Input processes
    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].wt = p[i].tat = 0;
    }
    
    int time = 0, completed = 0;
    
    printf("\nGantt Chart: ");
    
    while(completed < n) {
        int progress = 0;
        
        for(int i = 0; i < n; i++) {
            if(p[i].rt > 0) {
                progress = 1;
                printf("| P%d ", p[i].pid);
                
                if(p[i].rt > tq) {
                    time += tq;
                    p[i].rt -= tq;
                } else {
                    time += p[i].rt;
                    p[i].wt = time - p[i].bt;
                    p[i].tat = time;
                    p[i].rt = 0;
                    completed++;
                }
            }
        }
        
        if(!progress) break;
    }
    printf("|\n");
    
    // Calculate averages
    float total_wt = 0, total_tat = 0;
    
    printf("\nPID\tBurst\tWait\tTurnaround\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    
    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    
    return 0;
}
