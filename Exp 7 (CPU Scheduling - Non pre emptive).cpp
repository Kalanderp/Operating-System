#include <stdio.h>
struct Process {
    int pid, bt, at;
};
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    int wt[n], tat[n], ct[n];
    int completed = 0, t = 0, min_bt, index;
    float avgwt = 0, avgtat = 0;
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time and Arrival Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].bt, &p[i].at);
    }
    int done[n];
    for (int i = 0; i < n; i++)
        done[i] = 0;
    while (completed != n) {
        min_bt = 9999;
        index = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && done[i] == 0 && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                index = i;
            }
        }
        if (index == -1) {
            t++;  
            continue;
        }
        t += p[index].bt;      
        ct[index] = t;          
        tat[index] = ct[index] - p[index].at;
        wt[index] = tat[index] - p[index].bt;
        done[index] = 1;
        completed++;
    }
    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, wt[i], tat[i]);
        avgwt += wt[i];
        avgtat += tat[i];
    }
    printf("\nAverage Waiting Time: %.2f", avgwt/n);
    printf("\nAverage Turnaround Time: %.2f\n", avgtat/n);
    return 0;
}
