#include <stdio.h>
struct Process {
    int pid, bt, at, pr;
    int rt;        
};
int main() {
    int n, completed = 0, t = 0, min_pr, shortest;
    float avgwt = 0, avgtt = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for(int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("\nEnter Burst Time, Arrival Time and Priority for P%d: ", i+1);
        scanf("%d %d %d", &p[i].bt, &p[i].at, &p[i].pr);
        p[i].rt = p[i].bt;
    }
    int wt[n], tat[n];
    while(completed != n) {
        min_pr = 9999;
        shortest = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].at <= t && p[i].rt > 0 && p[i].pr < min_pr) {
                min_pr = p[i].pr;
                shortest = i;
            }
        }
        t++;
        if(shortest == -1)
            continue;
        p[shortest].rt--;
        if(p[shortest].rt == 0) {
            completed++;
            tat[shortest] = t - p[shortest].at;
            wt[shortest] = tat[shortest] - p[shortest].bt;
            avgwt += wt[shortest];
            avgtt += tat[shortest];
        }
    }
    printf("\nPID\tAT\tBT\tPR\tWT\tTAT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr, wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time: %.2f", avgwt/n);
    printf("\nAverage Turnaround Time: %.2f\n", avgtt/n);
    return 0;
}
