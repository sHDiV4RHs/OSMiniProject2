#include "types.h"
#include "stat.h"
#include "user.h"

int main(void)
{

   // printf(1, "Father pid is %d\n", getpid());
    sleep(10);
    for (int i = 0; i < 10; ++i) {
    	int pid = fork();
    }
    for(int i = 1; i < 1001; i++) {
        printf(1, "child %d prints for the %d time\n", getpid(), i);
    }

    // wait for child
    if(pid > 0) {
        while(wait() > 0);
    }

    exit();
}
