#include <stdio.h>
#include <time.h>
#include "omp.h"

static long num_steps = 100000000;
double step;

/**
 * @brief Calculates pi using omp parallel reduction, being sum the reduction
 * variable.
 * 
 * @param threadCount number of threads to use
 */
void calculatePi(int threadCount) {
    int i;
    double pi , sum = 0.0, start, end;

    start = omp_get_wtime();

    step = 1.0/(double) num_steps;

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

    printf("Threads count: %i, exec time: %f, pi: %.15f  \n", threadCount, (end - start), pi);
}

void main() {
    calculatePi(2);
    calculatePi(4);
    calculatePi(8);
    calculatePi(16);
    calculatePi(32);
    calculatePi(64);
}