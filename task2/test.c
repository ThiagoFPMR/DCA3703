#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_N 1000000000

int main() {
    static int v[MAX_N];  // vetor grande alocado fora da stack

    FILE *fp = fopen("resultados-O3.csv", "w");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Escreve cabeçalho no CSV
    fprintf(fp, "N,tempo_inicializacao,tempo_soma_dependente,tempo_soma_independente\n");

    for (int exp = 1; exp <= 8; exp++) {
        int N = 1;
        for (int i = 0; i < exp; i++) N *= 10;

        int i;
        long long soma;

        clock_t start, end;
        double tempo_init, tempo_dep, tempo_indep;

        // 1. Inicialização com cálculo simples
        start = clock();
        for (i = 0; i < N; i++) {
            v[i] = i * 2 + 1;
        }
        end = clock();
        tempo_init = ((double)(end - start)) / CLOCKS_PER_SEC;

        // 2. Soma com dependência entre iterações
        start = clock();
        soma = 0;
        for (i = 0; i < N; i++) {
            soma += v[i];
        }
        end = clock();
        tempo_dep = ((double)(end - start)) / CLOCKS_PER_SEC;

        // 3. Soma quebrando dependência (usando múltiplos acumuladores)
        start = clock();
        long long soma1 = 0, soma2 = 0, soma3 = 0, soma4 = 0;
        for (i = 0; i < N; i += 4) {
            if (i < N) soma1 += v[i];
            if (i + 1 < N) soma2 += v[i + 1];
            if (i + 2 < N) soma3 += v[i + 2];
            if (i + 3 < N) soma4 += v[i + 3];
        }
        soma = soma1 + soma2 + soma3 + soma4;
        end = clock();
        tempo_indep = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Imprime na tela (opcional)
        printf("\nN = %d\n", N);
        printf("Inicialização: %.6f s\n", tempo_init);
        printf("Soma com dependência: %.6f s\n", tempo_dep);
        printf("Soma sem dependência: %.6f s\n", tempo_indep);
        printf("Soma final: %lld\n", soma);

        // Escreve os dados no CSV
        fprintf(fp, "%d,%.6f,%.6f,%.6f\n", N, tempo_init, tempo_dep, tempo_indep);
    }

    fclose(fp);
    printf("\nResultados salvos em 'resultados.csv'\n");
    return 0;
}
