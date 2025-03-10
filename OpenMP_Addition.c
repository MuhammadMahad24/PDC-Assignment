#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 5  // Matrix size
#define NUM_THREADS 4  // Number of OpenMP threads
#define CHUNK_SIZE 2  // Chunk size for scheduling
#define NUM_RUNS 10  // Number of executions for averaging

void matrixAdditionParallel(int A[N][N], int B[N][N], long long C[N][N]) {
    int i, j;

    #pragma omp parallel for private(i, j) shared(A, B, C) num_threads(NUM_THREADS) schedule(dynamic, CHUNK_SIZE)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            // Using atomic to ensure each thread safely updates C[i][j]
            #pragma omp atomic write
            C[i][j] = (long long) A[i][j] + B[i][j];
        }
    }
}

void printMatrixInt(int M[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

void printMatrixLongLong(long long M[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%lld ", M[i][j]);
        }
        printf("\n");
    }
}
int main() {
    static int A[N][N], B[N][N];
    static long long C[N][N];  // Result matrix
    long long sum = 0;  // Sum of matrix elements
    double execution_times[NUM_RUNS];  // Store execution times

    srand(time(NULL));
    
    // Initialize matrices with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    // Print Matrices using a Critical Section to avoid race conditions
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        #pragma omp critical
        {
            if (omp_get_thread_num() == 0) {  // Print once
                printf("Matrix A:\n");
                printMatrixInt(A);
                printf("\nMatrix B:\n");
                printMatrixInt(B);
            }
        }
    }

    double total_time = 0;

    // Run 10 times and record execution times
    for (int run = 0; run < NUM_RUNS; run++) {
        double start = omp_get_wtime();
        matrixAdditionParallel(A, B, C);
        double end = omp_get_wtime();

        execution_times[run] = (end - start) * 1000;  // Convert to ms
        total_time += execution_times[run];
    }

    // Compute sum using Reduction
    #pragma omp parallel for reduction(+:sum) num_threads(NUM_THREADS) schedule(dynamic, CHUNK_SIZE)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sum += C[i][j];
        }
    }

    // Print Resultant Matrix C
    printf("\nResultant Matrix C (Sum):\n");
    printMatrixLongLong(C);
    
    // Print sum using Critical Section
    #pragma omp critical
    {
        printf("\nTotal sum of elements in C (Reduction result): %lld\n", sum);
    }

    // Print execution times
    printf("\nExecution Times for %d Runs (ms):\n", NUM_RUNS);
    for (int i = 0; i < NUM_RUNS; i++) {
        printf("Run %d: %.2f ms\n", i + 1, execution_times[i]);
    }
    
    // Compute and print average execution time
    double avg_time = total_time / NUM_RUNS;
    printf("\nAverage Execution Time: %.2f ms\n", avg_time);

    return 0;
}
