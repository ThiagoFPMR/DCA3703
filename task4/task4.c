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

// void complexSeries(int *a, int *b, int n)
// {
//     for (int i = 0; i < n; i++)
//         a[i] = cos(b[i]) + sin(sqrt(b[i])) + tan(b[i]) + log(b[i]) + exp(b[i]) + cos(cos(cos(cos(cos(cos(cos(cos(b[i]))))))));
// }

// void complexSeriesParallel(int *a, int *b, int n)
// {
//     #pragma omp parallel for
//     for (int i = 0; i < n; i++) 
//         a[i] = cos(b[i]) + sin(sqrt(b[i])) + tan(b[i]) + log(b[i]) + exp(b[i]) + cos(cos(cos(cos(cos(cos(cos(cos(b[i]))))))));
// }

int main()
{
    int n = 1000000;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    
    // Get num of threads
    int num_threads = omp_get_max_threads();

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
    FILE *file = fopen("vectorSum.csv", "a");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing\n");
    } else {
        // Write headers
        // Check if the file is empty before writing headers
        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0) {
            fprintf(file, "Time taken,Num threads\n");
        }
        // Write the time taken
        fprintf(file, "%.3f,%d\n", time, num_threads);
        fclose(file);
    }

    // Vector Sum Parallel
    start = omp_get_wtime();
    vectorSumParallel(a, b, n);
    end = omp_get_wtime();
    time = (end - start) * 1000000; // in microseconds
    printf("Vector Sum Parallel Time taken = %.3f us\n", time);
    file = fopen("vectorSumParallel.csv", "a");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing\n");
    } else {
        // Write headers
        // Check if the file is empty before writing headers
        fseek(file, 0, SEEK_END);
        if (ftell(file) == 0) {
            fprintf(file, "Time taken,Num threads\n");
        }
        // Write the time taken
        fprintf(file, "%.3f,%d\n", time, num_threads);
        fclose(file);
    }

    // // Cosine for Series
    // start = omp_get_wtime();
    // complexSeries(a, b, n);
    // end = omp_get_wtime();
    // time = (end - start) * 1000000; // in microseconds
    // printf("Cosine for Series Time taken = %.3f us\n", time);
    // file = fopen("ComplexSeries.csv", "a");
    // if (file == NULL) {
    //     fprintf(stderr, "Failed to open file for writing\n");
    // } else {
    //     // Write headers
    //     // Check if the file is empty before writing headers
    //     fseek(file, 0, SEEK_END);
    //     if (ftell(file) == 0) {
    //         fprintf(file, "Time taken,Num threads\n");
    //     }
    //     // Write the time taken
    //     fprintf(file, "%.3f,%d\n", time, num_threads);
    //     fclose(file);
    // }

    // // Cosine for Series Parallel
    // start = omp_get_wtime();
    // complexSeriesParallel(a, b, n);
    // end = omp_get_wtime();
    // time = (end - start) * 1000000; // in microseconds
    // printf("Cosine for Series Parallel Time taken = %.3f us\n", time);
    // file = fopen("ComplexSeriesParallel.csv", "a");
    // if (file == NULL) {
    //     fprintf(stderr, "Failed to open file for writing\n");
    // } else {
    //     // Write headers
    //     // Check if the file is empty before writing headers
    //     fseek(file, 0, SEEK_END);
    //     if (ftell(file) == 0) {
    //         fprintf(file, "Time taken,Num threads\n");;
    //     }
    //     // Write the time taken
    //     fprintf(file, "%.3f,%d\n", time, num_threads);
    //     fclose(file);
    // }

    // Free allocated memory
    free(a);
    free(b);

    return 0;
}
