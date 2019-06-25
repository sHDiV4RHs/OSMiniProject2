#include "types.h"
#include "stat.h"
#include "user.h"

int main(void)
{
    int wpid;

    printf(1, "Father pid is %d\n", getpid());
    sleep(10);
    int pid = fork();
    for(int i = 0; i < 50; i++) {
        printf(1, "process %d is printing for the %d time\n", getpid(), i);
    }

    // wait for child
    if(pid > 0) {
        while(wait() > 0);
    }

    exit();
}
