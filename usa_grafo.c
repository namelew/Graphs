#include <stdio.h>
#include <stdlib.h>
#include "aresta.h"
#include "grafo.h"
#include "fila.h"

int main() {
    int nv, na, nx, origin;
    Grafo *grafo;

    scanf("%d %d", &nv, &na);
    getchar();

    grafo = GRAFOconstroi(nv);

    for(int i=0; i < na; i++){
        Aresta a;
        scanf("%d %d", &a.v1, &a.v2);
        getchar();
        GRAFOinsere_aresta(grafo, a);
    }

    scanf("%d", &nx);
    getchar();

    for(int i = 0; i < nx; i++){
        scanf("%d", &origin);
        getchar();
        if(i > 0) printf("\n");
        GRAFOimprime_distancias_caminhos(grafo, origin);
    }

    GRAFOdestroi(grafo);

    return 0;
}
