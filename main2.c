#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
void multiplyMatrices(int A[N][N], int B[N][N], int C[N][N]) {
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
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    multiplyMatrices(A, B, C);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Matrix multiplication of %dx%d completed.\n", N, N);
    printf("Execution Time (Sequential): %.6f seconds\n", cpu_time_used);

    return 0;
}
