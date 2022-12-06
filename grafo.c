#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "fila.h"

#define INTMAX 2147483647

struct grafo {
    int num_v;
    int num_a;
    Lista **ladj;
};

Grafo *GRAFOconstroi(int num_v) {
    Grafo *g;

    g = malloc(sizeof(*g));

    g->num_v = num_v;
    g->num_a = 0;

    g->ladj = malloc(num_v * sizeof(Lista *));

    for (int i = 0; i < num_v; i++)
    {
        g->ladj[i] = LISTAconstroi();
    }

    return g;
}

void GRAFOinsere_aresta(Grafo *g, Aresta a) {
    
    if(g->ladj[a.v1]->procura == -1 && a.v1 != a.v2) {
        g->ladj[a.v1]->insere(g->ladj[a.v1], a.v2);
        g->num_a++;
    }
}

void GRAFOremove_aresta(Grafo *g, Aresta a) {
    if(g->ladj[a.v1]->remove(g->ladj[a.v1], a.v2) == 0) {
        g->num_a--;
    }
}

int GRAFOget_num_aresta(Grafo *g){
    return g->num_a;
}

int GRAFOget_num_vertice(Grafo *g) {
    return g->num_v;
}

void GRAFOdestroi(Grafo *g){
    for(int i = 0; i < g->num_v; i++){
        g->ladj[i]->destroi(g->ladj[i]);
    }
    free(g->ladj);
    free(g);
}