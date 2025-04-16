#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"
int main() {
    Estrada *estrada = getEstrada("cidades.txt");
    if (estrada) {
        printf("Número de cidades: %d\n", estrada->N);
        printf("Comprimento da estrada: %d\n", estrada->T);
        for (int i = 0; i < estrada->N; i++) {
            printf("Cidade %d: %s, Posicao: %d\n", i + 1, estrada->C[i].Nome, estrada->C[i].Posicao);
        }
        free(estrada->C);
        free(estrada);
    }
    double calc = calcularMenorVizinhanca("cidades.txt");
    printf("Menor vizinhança: %.2f\n", calc);
    return 0;
}
