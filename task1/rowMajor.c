#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"


int * columnMajorMatrix(int n, int m) {
    int *matrix = (int *)malloc(n * m * sizeof(int));
    if (matrix == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            matrix[i * m + j] = i + j;
        }
    }
    return matrix;
}

int * rowMajorMatrix(int n, int m) {
    int *matrix = (int *)malloc(n * m * sizeof(int));
    if (matrix == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i * m + j] = i + j;
        }
    }
    return matrix;
}

int * matrixByVectorProduct(int *matrix, int *vector, int n, int m) {
    int *result = (int *)malloc(n * sizeof(int));
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        result[i] = 0;
        for (int j = 0; j < m; j++) {
            result[i] += matrix[i * m + j] * vector[j];
        }
    }
    return result;
}

int main() {

    // Write header to csv file to contain results
    FILE *file;
    file = fopen("task1_row-major.csv", "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing\n");
        return 1;
    }
    fprintf(file, "n,time\n");
    fclose(file);

    for (int i = 1; i <= 18; i++) {
        int n = (int)pow(2, i);
        int *rowMatrix = rowMajorMatrix(n, n);
        int *vector = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            vector[j] = j;
        }
        clock_t start, end;
        int * result;
        double time;
        // Track time for matrix by vector product (row major)
        start = clock();
        result = matrixByVectorProduct(rowMatrix, vector, n, n);
        end = clock();
        time = (double)(end - start) / CLOCKS_PER_SEC * 1000000; // in microseconds
        printf("Row Major Matrix: n = %d, time taken = %.3f us\n", n, time);
        file = fopen("task1_row-major.csv", "a");
        if (file == NULL) {
            fprintf(stderr, "Failed to open file for writing\n");
        } else {
            fprintf(file, "%d,%.3f\n", n, time);
            fclose(file);
        }
        free(result);
        free(rowMatrix);
    }

    printf("Finished.\n");

    return 0;
}