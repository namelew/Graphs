#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

struct elemento{
    int dado;
    Elemento *proximo;
};

static void FILAenfileira(Fila *f, int dado){
    Elemento *new = malloc(sizeof(*new));
    new->dado = dado;
    new->proximo = NULL;

    if(!f->cadeca){
        f->cadeca = new;
        f->cauda = new;
        return;
    }

    f->cauda->proximo = new;
    f->cauda = new;
}

static int FILAdesenfileira(Fila *f){
    if(!(f->cadeca)) return -1;
    printf("%d\n", f->cadeca->dado);
    int dado = f->cadeca->dado;
    Elemento *aux = f->cadeca;

    f->cadeca = f->cadeca->proximo;

    free(aux);

    if(!(f->cadeca)) f->cauda = NULL;

    return dado;
}

static void FILAdestroi(Fila *f){
    if(!f->cadeca) return;
    Elemento *temp = f->cadeca;
    for(Elemento *aux = temp->proximo; aux != NULL; aux = aux->proximo){
        free(temp);
        temp = aux;
    }
    free(f);
}

Fila *FILAConstroi(){
    Fila *f = malloc(sizeof(*f));
    f->cadeca = NULL;
    f->cauda = NULL;
    f->desefileira = &FILAdesenfileira;
    f->enfileira = &FILAenfileira;
    f->destroi = &FILAdestroi;
    return f;
}