    #include <stdio.h>    
    #include <stdlib.h>
    #include <time.h>
    #include "omp.h"

    static long SIZE = 590;

    /**
     * @brief Defines a dynamic scheduling with different chunk sizes to execute
     * the multiply algorithm.
     * 
     * @param threadCount number of threads to use
     * @param chunkSize for dynamic allocation
     */
    void calculateMultiply(int threadCount, int chunkSize) {

        int a[SIZE][SIZE], 
            b[SIZE][SIZE], 
            mul[SIZE][SIZE],
            i=SIZE,
            j=SIZE,
            k=SIZE;  

        double start, end;

        // In order to use rand() we need to call the below functions
        srand(time(NULL));   
    
        // Init matrix a with random ints
        for(i=0;i<SIZE;i++) {    
            for(j=0;j<SIZE;j++) { 
                a[i][j] = rand() % 20;  
            }    
        }    
    
        // Init matrix b with random ints
        for(i=0;i<SIZE;i++) {    
            for(j=0;j<SIZE;j++) {    
                b[i][j] = rand() % 20;    
            }    
        }       

        // Init result matrix with 0
        for(i=0;i<SIZE;i++) {    
            for(j=0;j<SIZE;j++) {
                mul[i][j]=0;
            }
        }

        omp_set_schedule(omp_sched_dynamic, chunkSize);
        omp_set_num_threads(threadCount);

        start = omp_get_wtime();
        
        #pragma omp parallel for reduction(+:mul) shared(a, b) private(i,j,k)
        for(i=0;i<SIZE;i++) {    
            for(j=0;j<SIZE;j++) {
                for(k=0;k<SIZE;k++) {

                    int result = a[i][k] * b[k][j];

                    mul[i][j] += result;    
                }       
            }    
        }

        end = omp_get_wtime();

        printf("Threads count: %i, chunk size: %i, exec time: %f \n", threadCount, chunkSize, (end - start));
    }

    void main() {  
        calculateMultiply(2, 20);
        calculateMultiply(2, 50);
        calculateMultiply(2, 80);
        calculateMultiply(2, 100);

        calculateMultiply(4, 20);
        calculateMultiply(4, 50);
        calculateMultiply(4, 80);
        calculateMultiply(4, 100);

        calculateMultiply(8, 20);
        calculateMultiply(8, 50);
        calculateMultiply(8, 80);
        calculateMultiply(8, 100);

        calculateMultiply(16, 20);
        calculateMultiply(16, 50);
        calculateMultiply(16, 80);
        calculateMultiply(16, 100);

        calculateMultiply(32, 20);
        calculateMultiply(32, 50);
        calculateMultiply(32, 80);
        calculateMultiply(32, 100);

        calculateMultiply(64, 20);
        calculateMultiply(64, 50);
        calculateMultiply(64, 80);
        calculateMultiply(64, 100);
    }  