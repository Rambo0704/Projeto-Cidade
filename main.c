#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"
int main() {
    float calc = calcularMenorVizinhanca("cidades.txt");
    printf("%f",calc);
    return 0;
}
