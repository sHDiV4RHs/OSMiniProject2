
#include "types.h"
#include "stat.h"
#include "user.h"

int main(void)
{

    printf(1, "Father pid is %d\n", getpid());
    sleep(10);
    int childrenPID[30];
    int Ith = -1;
    for(int i = 0; i < 30; i++) {
        childrenPID[i] = fork();
        if(childrenPID[i] > 0) {
            if(childrenPID[i] % 3 == 0) {
                nice(childrenPID[i]);
            }
            else if(childrenPID[i] % 3 == 1) {
                nice(childrenPID[i]);
                nice(childrenPID[i]);
            }
        }

        // child
        if(childrenPID[i] == 0) {
            Ith = i;
            break;
        }
    }

    // children
    if(Ith != -1) {
        for(int i = 0; i < 500; i++) {
            printf(1, "%d \n", getpid());
        }
    }

    // wait for child
    else {
        int wTime[30];
        int rTime[30];
        int pid[30];
        for(int i = 0; i < 30; i++) {
            pid[i] = getperformancedata(&(wTime[i]), &(rTime[i]));
        }

        // print statistics
        double averageWTime = 0;
        double averageTTime = 0;
        double averageWTimeOfQ[3];
        double averageTTimeOfQ[3];
        int lenOfQ[3];
        for(int i = 0; i < 3; i++) {
            averageWTimeOfQ[i] = 0;
            averageTTimeOfQ[i] = 0;
            lenOfQ[i] = 0;
        }

        for(int i = 0; i < 30; i++) {
            printf(1, "pid: %d, waitingTime: %d, turnaroundTime: %d\n",
                    pid[i], wTime[i], wTime[i]+rTime[i]);
            averageWTime += 1./30 * wTime[i];
            averageTTime += 1./30 * (wTime[i]+rTime[i]);

            int QNumber = (pid[i]%3 + 1)%3;
            averageWTimeOfQ[QNumber] += wTime[i];
            averageTTimeOfQ[QNumber] += wTime[i]+rTime[i];
            lenOfQ[QNumber] += 1;
        }
        for(int i = 0; i < 3; i++) {
            printf(1, "Q[%d]-> len: %d, waitingTimeAverage: %d, turnaroundTimeAverage: %d\n",
                    i, lenOfQ[i], (int)(averageWTimeOfQ[i]/(lenOfQ[i])),
                   (int)(averageTTimeOfQ[i]/(lenOfQ[i])));
        }

        printf(1, "ALL-> waitingTimeAverage: %d, turnaroundTimeAverage: %d\n",
               (int)averageWTime, (int)averageTTime);
    }

    exit();
}

/** RESULT

pid: 14, waitingTime: 269, turnaroundTime: 336
pid: 8, waitingTime: 282, turnaroundTime: 353
pid: 5, waitingTime: 310, turnaroundTime: 390
pid: 26, waitingTime: 318, turnaroundTime: 408
pid: 32, waitingTime: 348, turnaroundTime: 455
pid: 20, waitingTime: 386, turnaroundTime: 506
pid: 11, waitingTime: 383, turnaroundTime: 511
pid: 29, waitingTime: 384, turnaroundTime: 509
pid: 23, waitingTime: 371, turnaroundTime: 504
pid: 17, waitingTime: 393, turnaroundTime: 574
pid: 6, waitingTime: 553, turnaroundTime: 636
pid: 9, waitingTime: 600, turnaroundTime: 710
pid: 12, waitingTime: 633, turnaroundTime: 755
pid: 15, waitingTime: 714, turnaroundTime: 856
pid: 18, waitingTime: 753, turnaroundTime: 862
pid: 21, waitingTime: 846, turnaroundTime: 959
pid: 24, waitingTime: 842, turnaroundTime: 986
pid: 30, waitingTime: 971, turnaroundTime: 1064
pid: 27, waitingTime: 942, turnaroundTime: 1087
pid: 4, waitingTime: 1115, turnaroundTime: 1191
pid: 33, waitingTime: 1055, turnaroundTime: 1221
pid: 7, waitingTime: 1202, turnaroundTime: 1315
pid: 10, waitingTime: 1256, turnaroundTime: 1347
pid: 13, waitingTime: 1314, turnaroundTime: 1450
pid: 16, waitingTime: 1339, turnaroundTime: 1446
pid: 22, waitingTime: 1436, turnaroundTime: 1532
pid: 19, waitingTime: 1436, turnaroundTime: 1604
pid: 25, waitingTime: 1524, turnaroundTime: 1655
pid: 28, waitingTime: 1583, turnaroundTime: 1676
pid: 31, waitingTime: 1639, turnaroundTime: 1764
Q[0]-> len: 10, waitingTimeAverage: 344, turnaroundTimeAverage: 454
Q[1]-> len: 10, waitingTimeAverage: 790, turnaroundTimeAverage: 913
Q[2]-> len: 10, waitingTimeAverage: 1384, turnaroundTimeAverage: 1498
ALL-> waitingTimeAverage: 839, turnaroundTimeAverage: 955 **/