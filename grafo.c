#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "heap.h"
#include "fila.h"
#include "pilha.h"

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
    }
}

static void buscaProfundidade(Grafo *g, int v, int *marcados){
    Pilha *p = PILHAconstroi();
    PILHAinsere(p, v);
    while(!PILHAvazia(p)){
        int w = PILHAremove(p);
        if(!marcados[w]){
            marcados[w] = 1;
            g->ladj[w]->empilha(g->ladj[w], p);
        }
    }
    PILHAdestroi(p);
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

int GRAFOehfconexo(Grafo *g){
    int *marcados = calloc(g->num_v, sizeof(int));
    for(int i = 0; i < g->num_v; i++){
        buscaProfundidade(g, i, marcados);
        for(int j = 0; j < g->num_v; j++){
            if (!marcados[j]){
                free(marcados);
                return 0;
            } 
        } 
        for(int j = 0; j < g->num_v; j++) marcados[j] = 0;
    }
    free(marcados);
    return 1;
}

void GRAFOmenor_caminho(Grafo *g, int v, int maximo){
    int pai[g->num_v], distancia[g->num_v];
    Heap *heap = HEAPconstroi(g->num_v);
    
    for(int i = 0; i < g->num_v; i++){
        pai[i] = -1;
        distancia[i] = INTMAX;
    }

    distancia[v] = 0;

    for(int i = 0; i < g->num_v; i++){
        HEAPinsere(heap, ITEM(i, distancia[i]));
    }

    dijkstra(g, heap, v, pai, distancia);

    for(int i = 0; i < g->num_v; i++){
        if(i == v) continue;

        printf("%d: ", i);
        if(distancia[i] > maximo || distancia[i] < 0) printf("sem caminho viavel partindo de %d\n", v);
        else{
            printf("%d, ", distancia[i]);
            int padastro = i;
            while(padastro != -1){
                printf("%d ", padastro);
                padastro = pai[padastro];
            }
            printf("\n");
        }
    }
}

void GRAFOimprime(Grafo *g){
    for(int i = 0; i < g->num_v; i++){
        printf("%d: ", i);
        g->ladj[i]->imprime(g->ladj[i]);
        printf("\n");
    }
}

void GRAFOdestroi(Grafo *g){
    for(int i = 0; i < g->num_v; i++){
        g->ladj[i]->destroi(g->ladj[i]);
    }
    free(g->ladj);
    free(g);
}