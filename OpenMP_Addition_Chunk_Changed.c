#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000  // Matrix size
#define CHUNK_SIZE 125  // Chunk size for scheduling

double A[N][N], B[N][N], C[N][N];  // Matrices

// Function to initialize matrices
void initialize_matrices() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;  
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }
    }
}

// Serial Matrix Multiplication
void serial_multiplication() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Static Scheduling - Default
void static_default() {
    #pragma omp parallel for collapse(2) schedule(static)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Static Scheduling - 4 Threads (Chunk Size 125)
void static_4_threads_chunk() {
    #pragma omp parallel for num_threads(4) collapse(2) schedule(static, CHUNK_SIZE)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Static Scheduling - 16 Threads (Chunk Size 125)
void static_16_threads_chunk() {
    #pragma omp parallel for num_threads(16) collapse(2) schedule(static, CHUNK_SIZE)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Dynamic Scheduling - Default
void dynamic_default() {
    #pragma omp parallel for collapse(2) schedule(dynamic)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Dynamic Scheduling - 4 Threads (Chunk Size 125)
void dynamic_4_threads_chunk() {
    #pragma omp parallel for num_threads(4) collapse(2) schedule(dynamic, CHUNK_SIZE)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Dynamic Scheduling - 16 Threads (Chunk Size 125)
void dynamic_16_threads_chunk() {
    #pragma omp parallel for num_threads(16) collapse(2) schedule(dynamic, CHUNK_SIZE)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Measure execution time
double measure_time(void (*func)()) {
    double start = omp_get_wtime();
    func();
    double end = omp_get_wtime();
    return end - start;
}

int main() {
    initialize_matrices();

    printf("Serial Execution Time: %lf seconds\n", measure_time(serial_multiplication));
    printf("Static Default Execution Time: %lf seconds\n", measure_time(static_default));
    printf("Static 4 Threads (Chunk Size 125) Execution Time: %lf seconds\n", measure_time(static_4_threads_chunk));
    printf("Static 16 Threads (Chunk Size 125) Execution Time: %lf seconds\n", measure_time(static_16_threads_chunk));
    printf("Dynamic Default Execution Time: %lf seconds\n", measure_time(dynamic_default));
    printf("Dynamic 4 Threads (Chunk Size 125) Execution Time: %lf seconds\n", measure_time(dynamic_4_threads_chunk));
    printf("Dynamic 16 Threads (Chunk Size 125) Execution Time: %lf seconds\n", measure_time(dynamic_16_threads_chunk));

    return 0;
}
