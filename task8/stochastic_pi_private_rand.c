#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "omp.h"
#include <time.h>

double monte_carlo_pi(int n)
{
    int count = 0;

    #pragma omp parallel
    {
        int private_count = 0;
        // Use a fixed seed for reproducibility
        # pragma omp for
        for (int i = 0; i < n; i++) {
            double x = (double)rand() / RAND_MAX;
            double y = (double)rand() / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                private_count++;
            }
        }

        // Combine the private counts into the global count
        #pragma omp critical
        {
            count += private_count;
        }
    }
    return (double)count / n * 4.0;
}

int main()
{
    int n = 1; // Change this to the desired number of iterations
    double pi;
    double start, end;
    double time;
    FILE *file;
    file = fopen("monte_carlo_pi_parallel_fixed.csv", "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing\n");
        return 1;
    } else {
        // Write headers
        fprintf(file, "N,Estimated Pi,Time taken\n");
    }
    for (int i = 0; i < 9; i++) 
    {
        n = n * 10;
        start = omp_get_wtime();
        pi = monte_carlo_pi(n);
        end = omp_get_wtime();
        time = (end - start) * 1000000; // in microseconds
        printf("Estimated Pi = %.6f\n", pi);
        printf("Time taken = %.3f us\n", time);
        file = fopen("monte_carlo_pi_parallel_fixed.csv", "a");
        if (file == NULL) {
            fprintf(stderr, "Failed to open file for writing\n");
        } else {
            // Write headers
            fprintf(file, "%d,%.6f,%.3f\n", n, pi, time);
            fclose(file);
        }
    }
    printf("Results written to monte_carlo_pi.csv\n");

    return 0;
}

