#ifndef HEAPH
#define HEAPH

#include "aresta.h"

typedef struct heap Heap;

void HEAPenpilha(Heap *h, Aresta a, int peso);
Aresta HEAPdesenpilha(Heap *h);
Heap *HEAPconstroi();

#endif /*#HEAPH*/