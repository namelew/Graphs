#ifndef HEAP_H

#define HEAP_H

#include <stdbool.h>
#include "item.h"

typedef struct heap Heap;

Heap *HEAPconstroi(int max_num_itens);

bool HEAPvazia(Heap *f);

bool HEAPcheia(Heap *f);

bool HEAPtem_indice(Heap *f, int ind);

void HEAPinsere(Heap *f, Item i);

Item HEAPremove(Heap *f);

Chave HEAPchave(Heap *f, int ind);

int HEAPdiminui_chave(Heap *f, int ind, Chave c);

void HEAPdestroi(Heap *f);

#endif /* HEAP_H */
