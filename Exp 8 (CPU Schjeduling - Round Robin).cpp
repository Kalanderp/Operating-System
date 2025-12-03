#include <stdio.h>
int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int bt[n], rt[n], wt[n], tat[n], at[n], t = 0, done = 0;
    for (int i = 0; i < n; i++) {
        printf("Enter AT and BT for P%d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    while (done != n) {
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= t) {
                if (rt[i] > tq) {
                    t += tq;
                    rt[i] -= tq;
                } else {
                    t += rt[i];
                    tat[i] = t - at[i];
                    wt[i] = tat[i] - bt[i];
                    rt[i] = 0;
                    done++;
                }
            } else if (at[i] > t) {
                t++;
            }
        }
    }
    float avgwt = 0, avgtat = 0;
    printf("\nPID\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], wt[i], tat[i]);
        avgwt += wt[i];
        avgtat += tat[i];
    }
    printf("\nAverage Waiting Time: %.2f", avgwt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avgtat / n);
    return 0;
}

