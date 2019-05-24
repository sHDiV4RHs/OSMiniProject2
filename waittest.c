#include "types.h"
#include "user.h"

int main(void)
{
    int *p1 = 0, *p2 = 0;
    printf(1, "getperformancedata: %d \n", getperformancedata(p1, p2));
    exit();
}
