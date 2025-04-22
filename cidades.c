#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"
FILE *abrirarq(const char *nomeArquivo, const char *modo);
void fechararq(FILE *arq);
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

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada)); //alocando memoria para os dados de estrada,como indicado pelo professor
    if (!estrada) {
        perror("Erro ao alocar memória para Estrada");
        fechararq(arquivo);
        return NULL;
    }

    fscanf(arquivo, "%d %d", &estrada->T, &estrada->N); //armazenando dados do csv para as variaveis da struct
    printf("Número de cidades: %d\n", estrada->N);
    printf("Comprimento da estrada: %d\n", estrada->T);
    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade)); //alocando memoria para os doados de cidade que etsa dentro da struct estrada.
    if (!estrada->C) {
        perror("Erro ao alocar memória para cidades");
        free(estrada);
        fechararq(arquivo);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {  //armazenando dados  para cada cidade do numero de cidades indicado.
        fscanf(arquivo, "%d %[^\n]s", &estrada->C[i].Posicao, estrada->C[i].Nome);
        printf("Cidade %d: %s, Posicao: %d\n",i+1, estrada->C[i].Nome, estrada->C[i].Posicao);
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

    double menorVizinhanca = -1;//inicializando com -1 para fazer a comparação com a vizinhança que inicializa com 0
    for (int i = 0; i < N; i++) {
        double vizinhanca = 0.0;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                vizinhanca = abs(cidades[i].Posicao - cidades[j].Posicao);//encontrei essa funçao abs que esta na biblioteca stdlib, ela retorna o valor absoluto de um inteiro, ou seja, o valor sem sinal.
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
                vizinhanca += abs(cidades[i].Posicao - cidades[j].Posicao); //funçao contida em stdlib,para sabe o valor absoluto(usei pois estamos tratando de um linha reta)
            }
        }
        if (vizinhanca == menorVizinhanca) {
            cidadeMenor = strdup(cidades[i].Nome); //pego uma variavel que esta em memoria alocada e atribuo a uma variavel sem emoria alocada.
        }
    }

    free(cidades);
    fechararq(arquivo);
    return cidadeMenor;
}