#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "heap.h"
#include "fila.h"

#define INTMAX 2147483647

struct grafo {
    int num_v;
    int num_a;
    Lista **ladj;
};

static void dijkstra(Grafo *g, Heap *heap, int v, int *pai, int *distancia){
    while(!HEAPvazia(heap)){
        Item w = HEAPremove(heap);
        g->ladj[w.ind]->explora(g->ladj[w.ind], heap, w.ind, pai, distancia);
        printf("\n PAI | DISTANCIA \n");
        for(int i = 0; i < g->num_v; i++) printf("%d %d\n", pai[i], distancia[i]);
    }
}

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
    Item result = g->ladj[a.v1]->procura(g->ladj[a.v1], a.v2);
    if(result.ind == -1 && a.v1 != a.v2) {
        result = ITEM(a.v2, a.peso);
        g->ladj[a.v1]->insere(g->ladj[a.v1], result);
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

void GRAFOmenor_caminho(Grafo *g, int v){
    int pai[g->num_v], distancia[g->num_v];
    Heap *heap = HEAPconstroi(g->num_v);
    
    for(int i = 0; i < g->num_v; i++){
        pai[i] = -1;
        distancia[i] = INTMAX;
        printf("%d,%d\n", pai[i], distancia[i]);
    }

    distancia[v] = 0;

    for(int i = 0; i < g->num_v; i++){
        HEAPinsere(heap, ITEM(i, distancia[i]));
    }

    dijkstra(g, heap, v, pai, distancia);

    for(int i = 0; i < g->num_v; i++){
        printf("(%d,%d,%d) ", i, pai[i], distancia[i]);
    }
    printf("\n");
}

void GRAFOimprime(Grafo *g){
    for(int i = 0; i < g->num_v; i++){
        g->ladj[i]->imprime(g->ladj[i]);
    }
}

void GRAFOdestroi(Grafo *g){
    for(int i = 0; i < g->num_v; i++){
        g->ladj[i]->destroi(g->ladj[i]);
    }
    free(g->ladj);
    free(g);
}