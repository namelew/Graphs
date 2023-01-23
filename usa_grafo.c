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
        x -= 1;
        y -= 1;
        switch (z) {
            case 1:
                GRAFOinsere_aresta(g, ARESTA(x,y,1));
                break;
            case 2:
                GRAFOinsere_aresta(g, ARESTA(x,y,1));
                GRAFOinsere_aresta(g, ARESTA(y,x,1));
                break;
            default:
                break;
        }
    }

    printf("%d\n", GRAFOehfconexo(g));

    GRAFOdestroi(g);

    return 0;
}
