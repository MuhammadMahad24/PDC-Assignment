#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1000  // Matrix size
#define NUM_THREADS 4  // Number of OpenMP threads
#define CHUNK_SIZE 2  // Chunk size for scheduling
#define NUM_RUNS 10  // Number of executions for averaging

void matrixAdditionParallel(int A[N][N], int B[N][N], long long C[N][N], int schedule_type) {
    int i, j;

    // Choose scheduling type dynamically
    if (schedule_type == 0) {
        #pragma omp parallel for private(i, j) shared(A, B, C) num_threads(NUM_THREADS) schedule(static, CHUNK_SIZE)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                C[i][j] = (long long) A[i][j] + B[i][j];
            }
        }
    } else {
        #pragma omp parallel for private(i, j) shared(A, B, C) num_threads(NUM_THREADS) schedule(dynamic, CHUNK_SIZE)
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                C[i][j] = (long long) A[i][j] + B[i][j];
            }
        }
    }
}

// void printMatrixInt(int M[N][N]) {
//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//             printf("%d ", M[i][j]);
//         }
//         printf("\n");
//     }
// }

// void printMatrixLongLong(long long M[N][N]) {
//     for (int i = 0; i < N; i++) {
//         for (int j = 0; j < N; j++) {
//             printf("%lld ", M[i][j]);
//         }
//         printf("\n");
//     }
    
// }
int main() {
    static int A[N][N], B[N][N];
    static long long C[N][N];  // Result matrix
    double serial_times[NUM_RUNS], static_times[NUM_RUNS], dynamic_times[NUM_RUNS];
    double total_serial = 0, total_static = 0, total_dynamic = 0;

    srand(time(NULL));
    
    // Initialize matrices with random values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }
    //  // Print Matrices
    //  printf("Matrix A:\n");
    //  printMatrixInt(A);
    //  printf("\nMatrix B:\n");
    //  printMatrixInt(B);

    double total_time = 0;

   
    // Run 10 times for each method
    for (int run = 0; run < NUM_RUNS; run++) {
        // Serial Execution
        double start = omp_get_wtime();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
        double end = omp_get_wtime();
        serial_times[run] = (end - start);
        total_serial += serial_times[run];

        // Parallel Execution (Static Scheduling)
        start = omp_get_wtime();
        matrixAdditionParallel(A, B, C, 0);
        end = omp_get_wtime();
        static_times[run] = (end - start);
        total_static += static_times[run];

        // Parallel Execution (Dynamic Scheduling)
        start = omp_get_wtime();
        matrixAdditionParallel(A, B, C, 1);
        end = omp_get_wtime();
        dynamic_times[run] = (end - start);
        total_dynamic += dynamic_times[run];
    }

    // Print Results
    printf("\nExecution Time Comparison:\n");
    printf("-------------------------------------------------------------\n");
    printf("| Run # | Serial Time (s) | Static Scheduling (s) | Dynamic Scheduling (s) |\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < NUM_RUNS; i++) {
        printf("| %4d  |   %.6f   |   %.6f   |   %.6f   |\n", 
               i + 1, serial_times[i], static_times[i], dynamic_times[i]);
    }
    printf("-------------------------------------------------------------\n");

    // Print Average Execution Times
    printf("\nAverage Execution Times:\n");
    printf("Serial Execution: %.6f sec\n", total_serial / NUM_RUNS);
    printf("Parallel (Static Scheduling): %.6f sec\n", total_static / NUM_RUNS);
    printf("Parallel (Dynamic Scheduling): %.6f sec\n", total_dynamic / NUM_RUNS);

    
}

