#include "stdio.h"
#include "stdlib.h"
#include "omp.h"
#include "math.h"

void vectorSum(int *a, int *b, int n)
{
    for (int i = 0; i < n; i++)
        a[i] = a[i] + b[i];
}

void vectorSumParallel(int *a, int *b, int n)
{
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
        a[i] = a[i] + b[i];
}

void complexSeries(int *a, int *b, int n)
{
    for (int i = 0; i < n; i++)
        a[i] = cos(b[i]) + sin(sqrt(b[i])) + tan(b[i]) + log(b[i]) + exp(b[i]);
}

void complexSeriesParallel(int *a, int *b, int n)
{
    #pragma omp parallel for
    for (int i = 0; i < n; i++) 
        a[i] = cos(b[i]) + sin(sqrt(b[i])) + tan(b[i]) + log(b[i]) + exp(b[i]);
}

int main()
{
    int n = 1000000;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    
    if (a == NULL || b == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        if (a) free(a);
        if (b) free(b);
        return 1;
    }
    
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Print max num of threads
    printf("Max num of threads = %d\n", omp_get_max_threads());

    double start, end;
    double time;

    // Vector Sum
    start = omp_get_wtime();
    vectorSum(a, b, n);
    end = omp_get_wtime();
    time = (end - start) * 1000000; // in microseconds
    printf("Vector Sum Time taken = %.3f us\n", time);
    FILE *file = fopen("task4.csv", "a");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing\n");
    } else {
        // Write headers
        fprintf(file, "Vector Sum,Time taken\n");
        fprintf(file, "%.3f\n", time);
        fclose(file);
    }

    // Vector Sum Parallel
    start = omp_get_wtime();
    vectorSumParallel(a, b, n);
    end = omp_get_wtime();
    time = (end - start) * 1000000; // in microseconds
    printf("Vector Sum Parallel Time taken = %.3f us\n", time);
    file = fopen("task4.csv", "a");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing\n");
    } else {
        // Write headers
        fprintf(file, "Vector Sum Parallel,Time taken\n");
        fprintf(file, "%.3f\n", time);
        fclose(file);
    }

    // Cosine for Series
    start = omp_get_wtime();
    complexSeries(a, b, n);
    end = omp_get_wtime();
    time = (end - start) * 1000000; // in microseconds
    printf("Cosine for Series Time taken = %.3f us\n", time);
    file = fopen("task4.csv", "a");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing\n");
    } else {
        // Write headers
        fprintf(file, "Cosine for Series,Time taken\n");
        fprintf(file, "%.3f\n", time);
        fclose(file);
    }

    // Cosine for Series Parallel
    start = omp_get_wtime();
    complexSeriesParallel(a, b, n);
    end = omp_get_wtime();
    time = (end - start) * 1000000; // in microseconds
    printf("Cosine for Series Parallel Time taken = %.3f us\n", time);
    file = fopen("task4.csv", "a");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing\n");
    } else {
        // Write headers
        fprintf(file, "Cosine for Series Parallel,Time taken\n");
        fprintf(file, "%.3f\n", time);
        fclose(file);
    }

    // Free allocated memory
    free(a);
    free(b);

    return 0;
}
