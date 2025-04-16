#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    FILE *arquivo = abrirarq(nomeArquivo, "r");
    int N, T;
    fscanf(arquivo, "%d %d", &T, &N);
    Cidade *cidades = (Cidade *)malloc(N * sizeof(Cidade));
    if (!cidades) {
        perror("Erro ao alocar memória para cidades");
        fechararq(arquivo);
        return -1;
    }
    for (int i = 0; i < N; i++) {
        fscanf(arquivo, "%d %[^\n]s", &cidades[i].Posicao, cidades[i].Nome);
    }

    double menorVizinhanca = -1;
    for (int i = 0; i < N; i++) {
        double vizinhanca = 0.0;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                vizinhanca += abs(cidades[i].Posicao - cidades[j].Posicao);//encontrei essa funçao abs que esta na biblioteca stdlib, ela retorna o valor absoluto de um inteiro, ou seja, o valor sem sinal.
            }
        }
        if (menorVizinhanca < 0 || vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(cidades);
    fechararq(arquivo);
    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    FILE *arquivo = abrirarq(nomeArquivo, "r");
    int N, T;
    fscanf(arquivo, "%d %d", &T, &N);
    Cidade *cidades = (Cidade *)malloc(N * sizeof(Cidade));
    if (!cidades) {
        perror("Erro ao alocar memória para cidades");
        fechararq(arquivo);
        return NULL;
    }
    for (int i = 0; i < N; i++) {
        fscanf(arquivo, "%d %[^\n]s", &cidades[i].Posicao, cidades[i].Nome);
    }

    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    char *cidadeMenor = NULL;

    for (int i = 0; i < N; i++) {
        double vizinhanca = 0.0;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                vizinhanca += abs(cidades[i].Posicao - cidades[j].Posicao);
            }
        }
        if (vizinhanca == menorVizinhanca) {
            cidadeMenor = strdup(cidades[i].Nome); // criar cópia segura da string
            break;
        }
    }

    free(cidades);
    fechararq(arquivo);
    return cidadeMenor;
}
