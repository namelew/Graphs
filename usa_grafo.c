#include <stdio.h>
#include <stdlib.h>
#include "aresta.h"
#include "grafo.h"
#include "fila.h"

int main() {
    Grafo *grafo;
    grafo = GRAFOconstroi(4);
    GRAFOinsere_aresta(grafo, ARESTA(0, 1));
    GRAFOinsere_aresta(grafo, ARESTA(1, 2));
    GRAFOinsere_aresta(grafo, ARESTA(2, 3));

    GRAFObuscaLargura(grafo, 0);

    GRAFOdestroi(grafo);

    return 0;
}
