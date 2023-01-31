#include <stdio.h>
#include <time.h>
#include "omp.h"

static long num_steps = 100000000;
double step;

/**
 * @brief Defines a static scheduling with different chunk sizes to execute 
 * pi calculation.
 * 
 * @param threadCount number of threads to use 
 * @param chunkSize for static allocation
 */
void calculatePi(int threadCount, int chunkSize) {
    int i;
    double pi , sum = 0.0, start, end;

    start = omp_get_wtime();

    step = 1.0/(double) num_steps;

    omp_set_schedule(omp_sched_static, chunkSize);
    omp_set_num_threads(threadCount);
    #pragma omp parallel for reduction(+:sum) shared(step) 
    for (i=0; i<num_steps;i++){

        double x, calc;

        x = (i+0.5)*step;
        calc = 4.0/(1.0 + x*x);

        sum += calc;
    }

    pi = step*sum;

    end = omp_get_wtime();

    printf("Threads count: %i, chunk size: %i, exec time: %f \n", threadCount, chunkSize, (end - start));
}

void main() {
    calculatePi(2, 10000);
    calculatePi(2, 20000);
    calculatePi(2, 50000);
    calculatePi(2, 100000);

    calculatePi(4, 10000);
    calculatePi(4, 20000);
    calculatePi(4, 50000);
    calculatePi(4, 100000);

    calculatePi(8, 10000);
    calculatePi(8, 20000);
    calculatePi(8, 50000);
    calculatePi(8, 100000);

    calculatePi(16, 10000);
    calculatePi(16, 20000);
    calculatePi(16, 50000);
    calculatePi(16, 100000);

    calculatePi(32, 10000);
    calculatePi(32, 20000);
    calculatePi(32, 50000);
    calculatePi(32, 100000);

    calculatePi(64, 10000);
    calculatePi(64, 20000);
    calculatePi(64, 50000);
    calculatePi(64, 100000);
}