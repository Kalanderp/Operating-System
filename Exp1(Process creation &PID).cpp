#include <stdio.h>
int main() {
    int parentPID = 1234;   
    int parentPPID = 1;    
    int childPID = 1235;    

    printf("Parent PID=%d PPID=%d\n", parentPID, parentPPID);
    printf("Child PID=%d PPID=%d\n", childPID, parentPID);

    return 0;
}
