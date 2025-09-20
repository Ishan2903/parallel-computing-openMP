#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>   
#define N 250
void readMatrix(const char *filename, int matrix[N][N]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }
    fclose(fp);
}

void multiplyMatricesParallel(int A[N][N], int B[N][N], int C[N][N], int num_threads) {
    #pragma omp parallel for num_threads(num_threads) collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int A[N][N], B[N][N], C[N][N];
    readMatrix("matrixA.txt", A);
    readMatrix("matrixB.txt", B);
    int thread_counts[] = {1, 2, 4, 8};
    int num_cases = sizeof(thread_counts) / sizeof(thread_counts[0]);
    for (int t = 0; t < num_cases; t++) {
        int threads = thread_counts[t];
        double start = omp_get_wtime();

        multiplyMatricesParallel(A, B, C, threads);

        double end = omp_get_wtime();
        printf("Threads: %d -> Execution Time: %.6f seconds\n", threads, end - start);
    }
    return 0;
}
