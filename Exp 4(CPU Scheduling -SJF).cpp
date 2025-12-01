#include <stdio.h>

typedef struct {
    int id;
    int exec_time;
} Process;

void schedule(Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].exec_time > proc[j + 1].exec_time) {
                Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }
}

int main() {
    Process proc[] = {{1, 5}, {2, 2}, {3, 1}, {4, 3}};
    int n = sizeof(proc) / sizeof(proc[0]);
    
    schedule(proc, n);
    
    printf("Scheduled Processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process ID: %d, Execution Time: %d\n", proc[i].id, proc[i].exec_time);
    }
    return 0;
}

