#include "math.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"

double leibnizPi(long int n) 
{
    double pi = 0;
    for (int i = 0; i < n; i++) {
        pi += pow(-1, i) / (2 * i + 1);
    }
    return pi * 4;
}

int main()
{
    clock_t start, end;
    double time, pi, pi_constant = M_PI;

    FILE *file = fopen("task3.csv", "a");
    // Write headers
    fprintf(file, "n,pi,error,time\n");

    for (int n = 0; n < 10; n++) {
        start = clock();
        pi = leibnizPi(pow(10, n));
        end = clock();
        time = (double)(end - start) / CLOCKS_PER_SEC * 1000000; // in microseconds
        printf("n = 10^\%d, pi = %.15f, error = %.10f, time taken = %.3f us\n", n, pi, pi_constant - pi, time);
        fprintf(file, "%d,%.10f,%.15f,%.3f\n", n, pi, pi_constant - pi, time);
    }

    return 0;
}