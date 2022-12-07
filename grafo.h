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

void GRAFOmenor_caminho(Grafo *g, int v, int maximo);

void GRAFOimprime(Grafo *g);

void GRAFOdestroi(Grafo *g);

#endif /* GRAFO_H */
