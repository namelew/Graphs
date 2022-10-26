#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "pilha.h"
#include "fila.h"

#define INTMAX 2147483647

struct grafo {
    int num_v;
    int num_a;
    int **matriz;
};

Grafo *GRAFOconstroi(int num_v) {
    Grafo *g;

    g = malloc(sizeof(*g));

    g->num_v = num_v;
    g->num_a = 0;

    g->matriz = malloc(num_v * sizeof(int*));

    for (int i = 0; i < num_v; i++)
    {
        g->matriz[i] = malloc(num_v * sizeof(int));
    }
    
    for (int i = 0; i < num_v; i++)
    {
        for (int j = 0; j < num_v; j++)
        {
            g->matriz[i][j] = 0;
        }
    }

    return g;
}

void GRAFOinsere_aresta(Grafo *g, Aresta a) {
    
    if(g->matriz[a.v1][a.v2] == 0 &&
       a.v1 != a.v2) {

        g->matriz[a.v1][a.v2] = 1;
        g->matriz[a.v2][a.v1] = 1;
        g->num_a++;
    }
}

void GRAFOremove_aresta(Grafo *g, Aresta a) {

    if(g->matriz[a.v1][a.v2] != 0) {

        g->matriz[a.v1][a.v2] = 0;
        g->matriz[a.v2][a.v1] = 0;
        g->num_a--;
    }
}

int GRAFOget_num_aresta(Grafo *g){
    return g->num_a;
}

int GRAFOget_num_vertice(Grafo *g) {
    return g->num_v;
}

void GRAFOimprime(Grafo *g) {

    for(int i = 0; i < g->num_v; i++) {
        printf("%d:", i);
        for (int j = 0; j < g->num_v; j++) {
            if(g->matriz[i][j])
                printf(" %d", j);
        }
        printf("\n");
    }
}

static bool caminho(Grafo *g, int v, int w, int marcado[], int indent) {
    if (v == w) {
        return true;
    }

    marcado[v] = 1;

    for (int u = 0; u < g->num_v; u++) {
        if (g->matriz[v][u] != 0) {
            if (marcado[u] == 0) {
                if (caminho(g, u, w, marcado, (indent + 4))) {
                    return true;
                }
            }
        }
    }

    return false;
}

static void buscaProfundidade(Grafo *g, int v, int *marcado){
    Pilha *p = PILHAconstroi();
    while(!PILHAvazia(p)){
        int w = PILHAremove(p);
        printf("%d\n", w);
        marcado[w] = 1;
        if(!marcado[w]){
            for(int i = 0; i < g->num_v; i++){
                if(g->matriz[w][i] && !marcado[i]){
                    PILHAinsere(p, i);
                }
            }
        }
    }
    PILHAdestroi(p);
}

static void buscaLargura(Grafo *g, int v, int *pai, int *marcado,int *distancia){
    Fila *f = FILAConstroi();
    marcado[v] = 1;
    pai[v] = -1;
    distancia[v] = 0;
    f->enfileira(f, v);
    while(f->cadeca){
        int w = f->desefileira(f);
        printf("%d ", w);
        for(int u = 0; u < g->num_v; u++){
            if(g->matriz[w][u] && !marcado[u]){
                marcado[u] = 1;
                pai[u] = w;
                distancia[u] = distancia[w] + g->matriz[w][u];
                f->enfileira(f, u);
            }
        }
    }
    f->destroi(f);
}

bool GRAFOcaminho(Grafo *g, int v, int w) {
    int marcado[g->num_v];

    for (int i = 0; i < g->num_v; i++) {
        marcado[i] = 0;
    }

    return caminho(g, v, w, marcado, 0);
}

void GRAFOdestroi(Grafo *g) {
    for (int i = 0; i < g->num_v; i++)
    {
        free(g->matriz[i]);
    }
    
    free(g->matriz);
    free(g);
}

static void exploraNodo(Grafo *g, Lista *lista, int start){
    for(int i = 0; i < g->num_v; i++){
        if(i != start && GRAFOcaminho(g, start, i)){
            lista->remove(lista, i);
        }
    }
}

bool GRAFOconexo(Grafo *g){
    int marcado[g->num_v];

    for (int i = 0; i < g->num_v; i++) marcado[i] = 0;

    buscaProfundidade(g, 0, marcado);

    for(int i=0; i < g->num_v; i++) if(!marcado[i]) return false;

    return true;
}

bool GRAFOaciclico(Grafo *g){
    for(int i = 0; i < g->num_v; i++){
        for(int j = 0; j < g->num_v; j++){
            if(g->matriz[i][j]){
                GRAFOremove_aresta(g, ARESTA(i, j));
                if(GRAFOcaminho(g, i, j)){
                    GRAFOinsere_aresta(g, ARESTA(i, j));
                    return false;
                }else{
                    GRAFOinsere_aresta(g, ARESTA(i, j));
                }
            }
        }
    }
    return true;
}

bool GRAFOscaminho(Grafo *g, int *s, int tam){
    int control[g->num_v];
    for(int i = 0; i < tam - 1; i++){
        if(control[s[i]]) return false;
        control[s[i]] = 1;
    }

    for(int i = 0; i < tam - 1; i++){
        if(!g->matriz[s[i]][s[i+1]]) return false;
    }
    return true;
}

void GRAFObuscaProfundidade(Grafo *g, int v){
    int marcado[g->num_v];

    for (int i = 0; i < g->num_v; i++) marcado[i] = 0;

    buscaProfundidade(g, v, marcado);
}

void GRAFObuscaLargura(Grafo *g, int v){
    int marcado[g->num_v], pai[g->num_v], distancia[g->num_v];

    for (int i = 0; i < g->num_v; i++) marcado[i] = 0;
    for (int i = 0; i < g->num_v; i++) pai[i] = -1;
    for (int i = 0; i < g->num_v; i++) distancia[i] = INTMAX;

    buscaLargura(g, v, pai, marcado, distancia);
}