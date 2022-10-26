#ifndef LISTA_H

#define LISTA_H

typedef struct no No;

typedef struct lista{
    No *cabeca;
    No *cauda;
    void (*insere)(struct lista *, int);
    int (*remove)(struct lista *, int);
    void (*destroi)(struct lista *);
    int (*conta)(struct lista *);
}Lista;

Lista *LISTAconstroi();

#endif /* ARESTA_H */