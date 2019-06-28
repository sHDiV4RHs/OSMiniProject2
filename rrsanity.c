#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {	
	int pid;
    for(int i = 0; i < 10; ++i) {
    	pid = fork();
    	if(pid == 0) {
    		printf(1, "child %d has been created.\n",i);
    		break;
    	}
    }

    if(pid == 0) {
        for(int i = 0; i < 1000; i++) {
            printf(1, "child %d prints for the %d time\n", getpid(), i);
        }
    }

    else {
        int wTime[10];
        int rTime[10];
        int childrenPID[10];

        // wait for children
        for(int i = 0; i < 10; i++) {
            childrenPID[i] = getperformancedata(&(wTime[i]), &(rTime[i]));
        }

        // print
        for(int i = 0; i < 10; i++) {
            printf(1, "pid: %d, waitingTime: %d, turnaroundTime: %d\n",
                   childrenPID[i], wTime[i], wTime[i] + rTime[i]);
        }
    }

    exit();
}

/** Result
pid: 4, waitingTime: 1785, turnaroundTime: 2838
pid: 5, waitingTime: 1942, turnaroundTime: 2987
pid: 6, waitingTime: 2492, turnaroundTime: 3581
pid: 7, waitingTime: 2851, turnaroundTime: 3919
pid: 8, waitingTime: 3044, turnaroundTime: 4119
pid: 9, waitingTime: 3256, turnaroundTime: 4215
pid: 10, waitingTime: 3633, turnaroundTime: 4725
pid: 11, waitingTime: 3900, turnaroundTime: 4969
pid: 12, waitingTime: 3964, turnaroundTime: 4965
pid: 13, waitingTime: 4045, turnaroundTime: 5033
**/