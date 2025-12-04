#include <stdio.h>

struct Process { int pid, bt, pri, rt, at, wt, tat; };

int main() {
    int n = 4, time = 0, completed = 0;
    struct Process p[] = {
        {1, 5, 2, 5, 0, 0, 0},
        {2, 3, 1, 3, 1, 0, 0},
        {3, 8, 3, 8, 2, 0, 0},
        {4, 6, 4, 6, 3, 0, 0}
    };
    
    printf("Execution: ");
    while (completed < n) {
        int idx = -1, hp = 999;
        for (int i = 0; i < n; i++)
            if (p[i].at <= time && p[i].rt > 0 && p[i].pri < hp) {
                hp = p[i].pri;
                idx = i;
            }
        
        if (idx != -1) {
            printf("P%d ", p[idx].pid);
            p[idx].rt--;
            time++;
            
            if (p[idx].rt == 0) {
                completed++;
                p[idx].tat = time - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
            }
        } else time++;
    }
    
    printf("\nPID\tBurst\tPri\tWait\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].pri, p[i].wt, p[i].tat);
    
    return 0;
}
