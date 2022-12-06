#include <stdio.h>
#include <stdlib.h>
#include "aresta.h"
#include "grafo.h"
#include "fila.h"

int main() {
    printf("Constroi grafo\n");
    Grafo *g = GRAFOconstroi(10);
    printf("Insere arestas\n");
    GRAFOinsere_aresta(g, ARESTA(1,2,3));
    GRAFOinsere_aresta(g, ARESTA(2,1,5));
    GRAFOinsere_aresta(g, ARESTA(3,2,2));
    printf("Remove arestas\n");
    GRAFOremove_aresta(g, ARESTA(1,2,3));
    printf("Destroi grafo\n");
    GRAFOdestroi(g);

    return 0;
}
