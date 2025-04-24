#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"
int main() {
    char *cidadeMenor = cidadeMenorVizinhanca("cidades.txt");
    printf("Cidade com menor vizinhanca: %s\n", cidadeMenor);
    
    return 0;
}
