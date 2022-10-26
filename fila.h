#ifndef FILAH
#define FILAH

typedef struct elemento Elemento;

typedef struct fila{
    Elemento *cadeca;
    Elemento *cauda;
    void (*enfileira)(struct fila *, int);
    int (*desefileira)(struct fila *);
    void (*destroi)(struct fila *);
}Fila;

Fila *FILAConstroi();

#endif /*FILAH*/