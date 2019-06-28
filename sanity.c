
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
pid: 29, waitingTime: 365, turnaroundTime: 461
pid: 5, waitingTime: 393, turnaroundTime: 496
pid: 11, waitingTime: 379, turnaroundTime: 486
pid: 14, waitingTime: 406, turnaroundTime: 513
pid: 8, waitingTime: 439, turnaroundTime: 549
pid: 23, waitingTime: 399, turnaroundTime: 512
pid: 32, waitingTime: 378, turnaroundTime: 488
pid: 17, waitingTime: 411, turnaroundTime: 529
pid: 26, waitingTime: 401, turnaroundTime: 527
pid: 20, waitingTime: 429, turnaroundTime: 569
pid: 9, waitingTime: 666, turnaroundTime: 752
pid: 15, waitingTime: 701, turnaroundTime: 804
pid: 6, waitingTime: 763, turnaroundTime: 862
pid: 12, waitingTime: 768, turnaroundTime: 870
pid: 21, waitingTime: 805, turnaroundTime: 911
pid: 18, waitingTime: 880, turnaroundTime: 980
pid: 30, waitingTime: 931, turnaroundTime: 1013
pid: 24, waitingTime: 932, turnaroundTime: 1025
pid: 27, waitingTime: 885, turnaroundTime: 1022
pid: 33, waitingTime: 954, turnaroundTime: 1033
pid: 25, waitingTime: 1167, turnaroundTime: 1238
pid: 7, waitingTime: 1227, turnaroundTime: 1349
pid: 13, waitingTime: 1287, turnaroundTime: 1385
pid: 10, waitingTime: 1268, turnaroundTime: 1394
pid: 16, waitingTime: 1308, turnaroundTime: 1419
pid: 22, waitingTime: 1394, turnaroundTime: 1454
pid: 19, waitingTime: 1358, turnaroundTime: 1462
pid: 28, waitingTime: 1374, turnaroundTime: 1465
pid: 34, waitingTime: 1395, turnaroundTime: 1482
pid: 31, waitingTime: 1401, turnaroundTime: 1499
Q[0]-> len: 10, waitingTimeAverage: 400, turnaroundTimeAverage: 513
Q[1]-> len: 10, waitingTimeAverage: 828, turnaroundTimeAverage: 927
Q[2]-> len: 10, waitingTimeAverage: 1317, turnaroundTimeAverage: 1414
ALL-> waitingTimeAverage: 848, turnaroundTimeAverage: 951 **/