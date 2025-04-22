#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"
int main() {
    Estrada *estrada = getEstrada("cidades.txt");
    double calc = calcularMenorVizinhanca("cidades.txt");
    printf("Menor vizinhança: %.2f\n", calc);
    return 0;
}
