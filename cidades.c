#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // para fabs()
#include "cidades.h"
FILE *abrirarq(const char *nomeArquivo, const char *modo) {
    FILE *arq = fopen(nomeArquivo, modo);
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        exit(1);
    }
    return arq;
}
void fechararq(FILE *arq) {
    if (arq) {
        fclose(arq);
    }
}
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = abrirarq(nomeArquivo, "r");

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        perror("Erro ao alocar memória para Estrada");
        fechararq(arquivo);
        return NULL;
    }

    fscanf(arquivo, "%d %d", &estrada->T, &estrada->N);
    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        perror("Erro ao alocar memória para cidades");
        free(estrada);
        fechararq(arquivo);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        fscanf(arquivo, "%d %[^\n]s", &estrada->C[i].Posicao, estrada->C[i].Nome);
    }

    fechararq(arquivo);
    return estrada;
}
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    double menorVizinhanca = estrada->T;
    for (int i = 0; i < estrada->N; i++) {
        double inicio, fim;

        if (i == 0)
            inicio = 0;
        else
            inicio = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;

        if (i == estrada->N - 1)
            fim = estrada->T;
        else
            fim = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;

        double vizinhanca = fim - inicio;
        if (vizinhanca < menorVizinhanca)
            menorVizinhanca = vizinhanca;
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhanca;
}
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    FILE *arquivo = abrirarq(nomeArquivo, "r");
    Estrada *estrada = getEstrada(nomeArquivo);
    char *cidadeMenor = NULL;
    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    for(int i = 0; i < estrada->N; i++) {
            if (cidadeMenor) free(cidadeMenor);
            cidadeMenor = strdup(estrada->C[i].Nome);
    }

    printf("Menor vizinhança: %s\n", cidadeMenor);


    fechararq(arquivo);
    return cidadeMenor;
}
