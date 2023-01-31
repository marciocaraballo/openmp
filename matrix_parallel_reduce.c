    #include <stdio.h>    
    #include <stdlib.h>
    #include <time.h>
    #include "omp.h"

    static long SIZE = 590;

    /**
     * @brief Caculates matrix multiply using omp parallel for reduction.
     * 
     * @param threadCount number of threads to use
     */
    void calculateMultiply(int threadCount) {

        int a[SIZE][SIZE], 
            b[SIZE][SIZE], 
            mul[SIZE][SIZE],
            i=SIZE,
            j=SIZE,
            k=SIZE;  

        double start, end;

        // In order to use rand() we need to call the below functions
        srand(time(NULL));   
    
        //Init matrix a with random ints
        for(i=0;i<SIZE;i++) {    
            for(j=0;j<SIZE;j++) { 
                a[i][j] = rand() % 20;  
            }    
        }    
    
        //Init matrix b with random ints
        for(i=0;i<SIZE;i++) {    
            for(j=0;j<SIZE;j++) {    
                b[i][j] = rand() % 20;    
            }    
        }       

        //Init result matrix with 0
        for(i=0;i<SIZE;i++) {    
            for(j=0;j<SIZE;j++) {
                mul[i][j]=0;
            }
        }

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

        printf("Threads count: %i, exec time: %f \n", threadCount, (end - start));
    }

    void main() {  
        calculateMultiply(2);
        calculateMultiply(4);
        calculateMultiply(8);
        calculateMultiply(16);
        calculateMultiply(32);
        calculateMultiply(64);
    }  