#ifndef CIDADES_H
#define CIDADES_H

typedef struct {
    char Nome[256]; // Nome da cidade
    int Posicao;    // Posição da cidade
} Cidade;

typedef struct {
    int N;       // Número de cidades
    int T;       // Comprimento da estrada
    Cidade *C;   // Vetor de cidades
} Estrada;

Estrada *getEstrada(const char *nomeArquivo);
double calcularMenorVizinhanca(const char *nomeArquivo);
char *cidadeMenorVizinhanca(const char *nomeArquivo);
#endif
