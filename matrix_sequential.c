    #include <stdio.h>    
    #include <stdlib.h>
    #include <time.h>

    static long SIZE = 590;

    void main(){  

        int a[SIZE][SIZE], 
            b[SIZE][SIZE], 
            mul[SIZE][SIZE],
            i=SIZE,
            j=SIZE,
            k=SIZE;  

        clock_t begin, end;
        double time_spent = 0.0;

        srand(time(NULL));  
    
        //Init matrix a with random ints
        for(i=0;i<SIZE;i++) {    
            for(j=0;j<SIZE;j++) { 
                a[i][j] = rand() % 99;  
            }    
        }    
    
        //Init matrix b with random ints
        for(i=0;i<SIZE;i++) {    
            for(j=0;j<SIZE;j++) {    
                b[i][j] = rand() % 99;    
            }    
        }       

        //Init result matrix with 0
        for(i=0;i<SIZE;i++) {    
            for(j=0;j<SIZE;j++) {
                mul[i][j]=0;
            }
        }

        begin = clock();

        //Multiply algorithm
        for(i=0;i<SIZE;i++) {    
            for(j=0;j<SIZE;j++) {    
                for(k=0;k<SIZE;k++) {   
                    mul[i][j] += a[i][k] * b[k][j];    
                }       
            }    
        }

        end = clock();

        time_spent += (double) (end - begin) / CLOCKS_PER_SEC;

        printf("Matrix multiply was done in time: %f \n", time_spent);  
    }  