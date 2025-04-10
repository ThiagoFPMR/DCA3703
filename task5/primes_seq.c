#include "stdio.h"
#include "stdlib.h"
#include "omp.h"

int count_primes(int n)
{
    int count = 0;
    for (int i = 2; i <= n; i++) {
        int is_prime = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            count++;
        }
    }
    return count;
}

int main()
{
    int n = 1; // Change this to the desired upper limit
    int count;
    double start, end;
    double time;
    FILE *file;
    file = fopen("primes_seq.csv", "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing\n");
        return 1;
    } else {
        // Write headers
        fprintf(file, "Count of Primes,Time taken\n");
    }
    for (int i = 0; i < 8; i++) 
    {
        n = n * 10;
        start = omp_get_wtime();
        count = count_primes(n);
        end = omp_get_wtime();
        time = (end - start) * 1000000; // in microseconds
        printf("Count of Primes = %d\n", count);
        printf("Time taken = %.3f us\n", time);
        file = fopen("primes_seq.csv", "a");
        if (file == NULL) {
            fprintf(stderr, "Failed to open file for writing\n");
        } else {
            // Write headers
            fprintf(file, "%d,%.3f\n", count, time);
            fclose(file);
        }
    }
    return 0;
}