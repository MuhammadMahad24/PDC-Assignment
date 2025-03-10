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
