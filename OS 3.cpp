#include <stdio.h>
#include <stdlib.h>

int main() {
    int A[100][4];
    int i, j, n, total = 0, index, temp;
    float avg_wt, avg_tat;
    
    printf("Enter number of process: ");
    scanf("%d", &n);
    
    printf("Enter Burst Time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]);
        A[i][0] = i + 1;
    }
    
    // Sort processes based on burst time (SJF)
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++) {
            if (A[j][1] < A[index][1]) {
                index = j;
            }
        }
        
        // Swap burst time
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;
        
        // Swap process ID
        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }
    
    // Calculate waiting time
    A[0][2] = 0;  // First process has 0 waiting time
    
    for (i = 1; i < n; i++) {
        A[i][2] = 0;
        for (j = 0; j < i; j++) {
            A[i][2] += A[j][1];
        }
        total += A[i][2];
    }
    
    avg_wt = (float)total / n;
    total = 0;
    
    printf("\nP\tBT\tWT\tTAT\n");
    printf("--------------------------------\n");
    
    // Calculate turnaround time and display results
    for (i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2];  // TAT = BT + WT
        total += A[i][3];
        printf("P%d\t%d\t%d\t%d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
    }
    
    avg_tat = (float)total / n;
    
    printf("\nAverage Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);
    
    system("pause");  // Keep console window open in DEV C++
    return 0;
}
