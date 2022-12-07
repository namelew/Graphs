#ifndef LISTA_H

#define LISTA_H
#include "item.h"
#include "heap.h"

typedef struct no No;

typedef struct lista{
    No *cabeca;
    No *cauda;
    void (*insere)(struct lista *, Item);
    int (*remove)(struct lista *, int);
    void (*destroi)(struct lista *);
    int (*conta)(struct lista *);
    void (*imprime)(struct lista *);
    void (*explora)(struct lista *, Heap *, int, int *, int *);
    Item (*procura)(struct lista *, int);
}Lista;

Lista *LISTAconstroi();

#endif /* ARESTA_H */