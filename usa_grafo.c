#include <stdio.h>
#include <stdlib.h>
#include "aresta.h"
#include "grafo.h"
#include "fila.h"

int main() {
    printf("Constroi grafo\n");
    Grafo *g = GRAFOconstroi(6);
    printf("Insere arestas\n");

    GRAFOinsere_aresta(g, ARESTA(0,2,3));
    GRAFOinsere_aresta(g, ARESTA(0,1,2));
    GRAFOinsere_aresta(g, ARESTA(0,4,3));
    GRAFOinsere_aresta(g, ARESTA(1,2,5));
    GRAFOinsere_aresta(g, ARESTA(1,3,1));
    GRAFOinsere_aresta(g, ARESTA(2,0,9));
    GRAFOinsere_aresta(g, ARESTA(3,5,2));
    GRAFOinsere_aresta(g, ARESTA(3,2,3));
    GRAFOinsere_aresta(g, ARESTA(4,0,2));
    GRAFOinsere_aresta(g, ARESTA(5,3,5));
    GRAFOinsere_aresta(g, ARESTA(5,1,7));
    GRAFOinsere_aresta(g, ARESTA(5,0,4));

    GRAFOmenor_caminho(g, 0);

    GRAFOdestroi(g);

    return 0;
}
