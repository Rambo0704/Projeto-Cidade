#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // para fabs()
#include "cidades.h"
FILE *abrirarq(const char *nomeArquivo, const char *modo) {//função para facilitar abertura do arquivo
    FILE *arq = fopen(nomeArquivo, modo);
    if (arq == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        exit(1);
    }
    return arq;
}
void fechararq(FILE *arq) {//função para facilitar o fechamento do arquivo
    if (arq) {
        fclose(arq);
    }
}
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = abrirarq(nomeArquivo, "r");

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada)); //alocando memória para Estrada
    if (!estrada) { 
        perror("Erro ao alocar memória para Estrada");
        fechararq(arquivo);
        return NULL;
    }
    fscanf(arquivo, "%d %d", &estrada->T, &estrada->N); //salvando o tamanho da estrada e o número de cidades
    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade)); //alocando memoria para cidades como o C é uma struct dentro de outra struct
    if (!estrada->C) {
        perror("Erro ao alocar memória para cidades");
        free(estrada);
        fechararq(arquivo);
        return NULL;
    }
    //lendo as cidades do arquivo e salvando na struct
    for (int i = 0; i < estrada->N; i++) {
        fscanf(arquivo, "%d %[^\n]s", &estrada->C[i].Posicao, estrada->C[i].Nome);
    }
    //estrada,nem cidade,foram liberadas suas memorias,devem ser liberadas nas funçoes que as chamam. :)
    fechararq(arquivo);
    return estrada;
}
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    for (int i = 0; i < estrada->N - 1; i++) { //usando o bouble sort para ordenar as cidades por posição,na reta.
        for (int j = 0; j < estrada->N - i - 1; j++) {
            if (estrada->C[j].Posicao > estrada->C[j + 1].Posicao) {
                Cidade temp = estrada->C[j];
                estrada->C[j] = estrada->C[j + 1];
                estrada->C[j + 1] = temp;
            }
        }
    }
    double menorVizinhanca = estrada->T; //definindo o menor vizinhanca como o tamanho da estrada,para fazer a comparação
    for (int i = 0; i < estrada->N; i++) { //loop para pegar cada posição de cidade e calcular a vizinhanca
        double inicio, fim; //defindo o inicio e o fim da vizinhanca

        if (i == 0)
            inicio = 0;
        else
            inicio = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0; //se for a primeira cidade, o inicio é 0, senão é a média entre a cidade anterior e a atual

        if (i == estrada->N - 1)
            fim = estrada->T;
        else
            fim = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0; //se for a última cidade, o fim é o tamanho da estrada, senão é a média entre a cidade atual e a próxima

        double vizinhanca = fim - inicio;
        if (vizinhanca < menorVizinhanca)
            menorVizinhanca = vizinhanca;
    }
    return menorVizinhanca;
}
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return NULL;
    for (int i = 0; i < estrada->N - 1; i++) { //ordeno novamente as cidades na reta
        for (int j = 0; j < estrada->N - i - 1; j++) {
            if (estrada->C[j].Posicao > estrada->C[j + 1].Posicao) {
                Cidade temp = estrada->C[j];
                estrada->C[j] = estrada->C[j + 1];
                estrada->C[j + 1] = temp;
            }
        }
    }
    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo); //uso a função para calcular o menor vizinhanca
    char *cidadeMenor = NULL;
    for (int i = 0; i < estrada->N; i++) {
        double inicio;
        if (i == 0) {
            inicio = 0;
        } else {
            inicio = (estrada->C[i].Posicao + estrada->C[i - 1].Posicao) / 2.0;
        }

        double fim;
        if (i == estrada->N - 1) {
            fim = estrada->T;
        } else {
            fim = (estrada->C[i].Posicao + estrada->C[i + 1].Posicao) / 2.0;
        }

        double vizinhanca = fim - inicio;
        if (vizinhanca == menorVizinhanca) {
            free(cidadeMenor); //libero a memoria da cidade menor
            cidadeMenor = strdup(estrada->C[i].Nome); //uso strdup da biblioteca string.h para alocar memoria para a string e copiar o nome da cidade
            break;
        }
    }
    free(estrada->C); //agora sim como é a ultima funçao eu libero a memoria da cidade
    free(estrada);//libero a memoria da estrada
    return cidadeMenor;
}

