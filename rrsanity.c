#include "types.h"
#include "stat.h"
#include "user.h"

int main(void)
{	
	int pid;
    for (int i = 0; i < 10; ++i) {
    	pid = fork();
    	if(pid == 0)
    		break;
    }

    for(int i = 0 && pid == 0; i < 10; i++) {
        printf(1, "child %d prints for the %d time\n", getpid(), i);
    }

    // wait for child
    int wTime[10];
        int rTime[10];
        for(int i = 0; i < 10; i++) {
            pid = getperformancedata(&(wTime[i]), &(rTime[i]));
            printf(1, "pid: %d, waitingTime: %d, turnaroundTime: %d\n",
                    pid, wTime, wTime[i]+rTime);
        }

    exit();
}
