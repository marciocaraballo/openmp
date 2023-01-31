#include <stdio.h>
#include <time.h>
#include "omp.h"

static long num_steps = 100000000;
double step;

/**
 * @brief Modified version of pi_parallel.c 
 * The beloew code tries to avoid the data dependency generated in the previous parallel version 
 * with the sum of the result to the accum variable, without using omp reduce.
 * A temporary data array was defined, based on the desired threads execution, each thread will add 
 * up to a specific position in the array. Once all threads are done, the values in each position 
 * of the array will be added together, simulating the use of an accumulation variable. 
 * The code tries to avoid the definition of a critical code section for threads.
 * 
 * @param threadCount number of threads to use
 */
void calculatePi(int threadCount) {
    
    int i, ts;
    double pi , sum = 0.0, start, end;

    omp_set_num_threads(threadCount);

    double tempSum[threadCount];

    for (ts = 0; ts < threadCount; ts++) {
        tempSum[ts] = 0.0;
    }

    start = omp_get_wtime();

    step = 1.0/(double) num_steps;

    #pragma omp parallel for private(i) shared(step, tempSum)
    for (i=0; i<num_steps;i++){

        double x, calc;
        int threadNum = omp_get_thread_num();

        x = (i+0.5)*step;
        calc = 4.0/(1.0 + x*x);

        tempSum[threadNum] += calc;
    }

    //Should be executed by main thread sequentially
    for(ts = 0; ts < threadCount; ts++) {
        sum += tempSum[ts];
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