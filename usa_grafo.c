#include <stdio.h>
#include <stdlib.h>
#include "aresta.h"
#include "grafo.h"
#include "fila.h"

int main() {
    int c,v,r,x;

    scanf("%d %d", &c, &v);
    getchar();

    Grafo *g = GRAFOconstroi(c);

    for(int i = 0; i < v; i++){
        int y,z;
        scanf("%d %d %d", &x, &y, &z);
        getchar();

        GRAFOinsere_aresta(g, ARESTA(x,y,z));
    }

    scanf("%d", &r);
    getchar();

    for(int i = 0; i < r; i++){
        int m;
        scanf("%d %d", &x, &m);
        getchar();

        GRAFOmenor_caminho(g, x, m);
    }

    GRAFOdestroi(g);

    return 0;
}
