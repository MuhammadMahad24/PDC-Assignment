#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000  // Matrix size (N x N)

void matrixAdditionSequential(int A[N][N], int B[N][N], int C[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
} 
void printMatrix(int M[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}
int main() {
    static int A[N][N], B[N][N], C[N][N];

    // Initialize matrices with random values
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }
    // Sequential execution
    clock_t start = clock();
    matrixAdditionSequential(A, B, C);
    clock_t end = clock();

     // Print Resultant Matrix
     printf("\nResultant Matrix C (Sum):\n");
     printMatrix(C);

    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Sequential Execution Time: %.2f ms\n", time_taken);

    return 0;
} 
