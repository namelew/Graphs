#ifndef GRAFO_H

#define GRAFO_H

#include <stdbool.h>
#include "aresta.h"
#include "lista.h"

typedef struct grafo Grafo;

Grafo *GRAFOconstroi(int N);

void GRAFOinsere_aresta(Grafo *g, Aresta a);

void GRAFOremove_aresta(Grafo *g, Aresta a);

int GRAFOget_num_aresta(Grafo *g);

int GRAFOget_num_vertice(Grafo *g);

void GRAFOimprime(Grafo *g);

bool GRAFOcaminho(Grafo *g, int v, int w);

void GRAFOdestroi(Grafo *g);

bool GRAFOconexo(Grafo *g);

bool GRAFOaciclico(Grafo *g);

bool GRAFOscaminho(Grafo *g, int *s, int tam);

void GRAFObuscaProfundidade(Grafo *g, int v);

void GRAFObuscaLargura(Grafo *g, int v);

void GRAFOimprime_distancias_caminhos(Grafo *g, int v);

#endif /* GRAFO_H */
