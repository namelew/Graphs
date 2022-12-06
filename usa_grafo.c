#include <stdio.h>
#include <stdlib.h>
#include "aresta.h"
#include "grafo.h"
#include "fila.h"

int main() {
    Grafo *g = GRAFOconstroi(10);

    GRAFOinsere_aresta(g, ARESTA(1,2));
    GRAFOinsere_aresta(g, ARESTA(2,1));
    GRAFOinsere_aresta(g, ARESTA(3,2));
    GRAFOremove_aresta(g, ARESTA(1,2));
    GRAFOdestroi(g);

    return 0;
}
