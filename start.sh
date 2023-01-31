#! /bin/bash

if [[ $1 == "matrix" ]]; then

    echo "Se compilaran los ejecutables de cada version del algoritmo de matrices"

    gcc -o matrix_sequential matrix_sequential.c
    gcc -o matrix_parallel -fopenmp matrix_parallel.c
    gcc -o matrix_parallel_reduce -fopenmp matrix_parallel_reduce.c
    gcc -o matrix_parallel_reduce_scheduling -fopenmp matrix_parallel_reduce_scheduling.c

    echo -e "Finalizada compilacion de los algoritmos \n"

    echo -e "Multiplicacion de matrices secuencial \n"
    ./matrix_sequential

    echo -e "\nMultiplicacion de matrices con directiva parallel for \n"
    ./matrix_parallel

    echo -e "\nMultiplicacion de matrices con directiva parallel for reduction \n"
    ./matrix_parallel_reduce

    echo -e "\nMultiplicacion de matrices con directiva parallel for reduction y dynamic scheduling \n"
    ./matrix_parallel_reduce_scheduling

elif [[ $1 == "pi" ]]; then

    echo "Se compilaran los ejecutables de cada version del algoritmo de pi"

    gcc -o pi_sequential pi_sequential.c
    gcc -o pi_parallel -fopenmp pi_parallel.c
    gcc -o pi_parallel_without_atomic -fopenmp pi_parallel_without_atomic.c
    gcc -o pi_parallel_reduce -fopenmp pi_parallel_reduce.c
    gcc -o pi_parallel_reduce_scheduling -fopenmp pi_parallel_reduce_scheduling.c

    echo -e "Finalizada compilacion de los algoritmos \n"

    echo -e "Calculo de pi secuencial \n"
    ./pi_sequential

    echo -e "\nCalculo de pi con directiva parallel for \n"
    ./pi_parallel

    echo -e "\nCalculo de pi con directiva parallel sin atomic for \n"
    ./pi_parallel_without_atomic

    echo -e "\nCalculo de pi con directiva parallel for reduction \n"
    ./pi_parallel_reduce

    echo -e "\nCalculo de pi directiva parallel for reduction y static scheduling \n"
    ./pi_parallel_reduce_scheduling
else 
    echo "Argumento no valido. Elija ./start.sh pi o ./start.sh matrix"
fi 