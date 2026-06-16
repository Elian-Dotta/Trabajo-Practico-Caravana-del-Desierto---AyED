#include "timer.h"

void wait(double segundos)
{
    clock_t inicio = clock();

    while ((double)(clock() - inicio) / CLOCKS_PER_SEC < segundos)
        ;
}
