#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 16             // Tamanho da grade (NxNxN)
#define STEPS 1000       // Número de passos de tempo
#define DT 0.01          // Intervalo de tempo
#define DX 1.0           // Espaçamento da grade
#define VISCOSITY 0.1    // Coeficiente de viscosidade

// Macros para acesso rápido
#define IX(i,j,k) ((i) + N*(j) + N*N*(k))

void add_perturbation(double *u, double *v, double *w) {
    int cx = N / 2, cy = N / 2, cz = N / 2; // Center of the grid
    int radius = 2; // Radius of the perturbation region

    for (int k = cz - radius; k <= cz + radius; k++) {
        for (int j = cy - radius; j <= cy + radius; j++) {
            for (int i = cx - radius; i <= cx + radius; i++) {
                if (i >= 0 && i < N && j >= 0 && j < N && k >= 0 && k < N) {
                    int idx = IX(i, j, k);
                    u[idx] += 1.0; // Add perturbation to the u-component
                    v[idx] += 0.5; // Add perturbation to the v-component
                    w[idx] += 0.2; // Add perturbation to the w-component
                }
            }
        }
    }
}

void step(double *u, double *v, double *w, double *u_new, double *v_new, double *w_new) {
    double laplacian;
    int i, j, k;

    for (k = 1; k < N-1; k++) {
        for (j = 1; j < N-1; j++) {
            for (i = 1; i < N-1; i++) {
                int idx = IX(i, j, k);

                // Laplaciano da velocidade u
                laplacian = (u[IX(i+1,j,k)] + u[IX(i-1,j,k)] +
                             u[IX(i,j+1,k)] + u[IX(i,j-1,k)] +
                             u[IX(i,j,k+1)] + u[IX(i,j,k-1)] -
                             6.0 * u[idx]) / (DX * DX);

                u_new[idx] = u[idx] + VISCOSITY * DT * laplacian;

                // Laplaciano da velocidade v
                laplacian = (v[IX(i+1,j,k)] + v[IX(i-1,j,k)] +
                             v[IX(i,j+1,k)] + v[IX(i,j-1,k)] +
                             v[IX(i,j,k+1)] + v[IX(i,j,k-1)] -
                             6.0 * v[idx]) / (DX * DX);

                v_new[idx] = v[idx] + VISCOSITY * DT * laplacian;

                // Laplaciano da velocidade w
                laplacian = (w[IX(i+1,j,k)] + w[IX(i-1,j,k)] +
                             w[IX(i,j+1,k)] + w[IX(i,j-1,k)] +
                             w[IX(i,j,k+1)] + w[IX(i,j,k-1)] -
                             6.0 * w[idx]) / (DX * DX);

                w_new[idx] = w[idx] + VISCOSITY * DT * laplacian;
            }
        }
    }
}

void swap(double **a, double **b) {
    double *tmp = *a;
    *a = *b;
    *b = tmp;
}

void save_to_file(const char *filename, double *u, double *v, double *w, int t) {
    FILE *file = fopen(filename, "a"); // Open in append mode
    if (!file) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", filename);
        return;
    }

    for (int k = 0; k < N; k++) {
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                int idx = IX(i, j, k);
                fprintf(file, "%d,%d,%d,%d,%.5f,%.5f,%.5f\n", t, i, j, k, u[idx], v[idx], w[idx]);
            }
        }
    }

    fclose(file);
}

int main() {
    int size = N * N * N;
    double *u = calloc(size, sizeof(double));
    double *v = calloc(size, sizeof(double));
    double *w = calloc(size, sizeof(double));
    double *u_new = calloc(size, sizeof(double));
    double *v_new = calloc(size, sizeof(double));
    double *w_new = calloc(size, sizeof(double));

    // Cria arquivo e o cabecalho
    char * filename = "resultados.csv";
    FILE *file = fopen(filename, "w");
    fprintf(file, "t,i,j,k,u,v,w\n");
    fclose(file);

    if (!u || !v || !w || !u_new || !v_new || !w_new) {
        printf("Erro de alocação de memória.\n");
        return 1;
    }

    for (int t = 0; t < STEPS; t++) {
        if (t == 10) {
            printf("Adicionando perturbação...\n");
            add_perturbation(u, v, w);
        }

        step(u, v, w, u_new, v_new, w_new);

        swap(&u, &u_new);
        swap(&v, &v_new);
        swap(&w, &w_new);

        // Salvar resultados a cada 100 passos
        if (t % 10 == 0) {
            printf("Salvando resultados no passo %d...\n", t);
            save_to_file(filename, u, v, w, t);
        }

        if (t % 10 == 0) {
            printf("Passo %d concluído.\n", t);
            // printff("Velocidade no passo %d: u=%.5f, v=%.5f, w=%.5f\n", t, u[IX(N/2, N/2, N/2)], v[IX(N/2, N/2, N/2)], w[IX(N/2, N/2, N/2)]);
        }
    }

    // Salvar resultados (por exemplo: no centro)
    int center = IX(N/2, N/2, N/2);
    printf("Velocidade final no centro: u=%.5f, v=%.5f, w=%.5f\n", u[center], v[center], w[center]);

    free(u); free(v); free(w);
    free(u_new); free(v_new); free(w_new);

    return 0;
}
