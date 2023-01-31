#include <stdio.h>
#include <time.h>
#include "omp.h"

static long num_steps = 100000000;
double step;

// Secuential version
void main() {

    int i;
    double pi , x, sum = 0.0, time_spent = 0.0;
    clock_t begin, end;

    begin = clock();

    step = 1.0/(double) num_steps;

    for (i=0; i<num_steps;i++){
        x = (i+0.5)*step;
        sum = sum + 4.0/(1.0 + x*x);
    }

    pi = step*sum;

    end = clock();

    time_spent += (double) (end - begin) / CLOCKS_PER_SEC;

    printf("The calculated value of pi: %.15f in time: %f \n", pi, time_spent);

}