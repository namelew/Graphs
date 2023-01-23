#include "lista.h"
#include "aresta.h"
#include <stdlib.h>
#include <stdio.h>

struct no{
    Item data;
    struct no *proximo;
    struct no *anterior;
};

static void LISTAinsere(Lista *lista, Item data){
    No *novo = malloc(sizeof(*novo));
    novo->data = data;
    novo->anterior = NULL;
    novo->proximo = NULL;

    if(!lista->cabeca){
        lista->cabeca = novo;
        lista->cauda = novo;
        return;    
    }

    novo->proximo = lista->cabeca;
    lista->cabeca->anterior = novo;

    lista->cabeca = novo;
}

static int LISTAremove(Lista *lista, int data){
    No *temp = NULL;

    if(!lista->cabeca) return 0;

    if(lista->cabeca->data.ind == data){
        temp = lista->cabeca;
        if(!lista->cabeca->proximo){
            free(temp);
            lista->cabeca = NULL;
            lista->cauda = NULL;
            return 1;    
        }
        lista->cabeca = lista->cabeca->proximo;
        lista->cabeca->anterior = NULL;
        free(temp);
        return 1;
    }

    if(lista->cauda->data.ind == data){
        temp = lista->cauda;
        lista->cauda = temp->anterior;
        lista->cauda->proximo = NULL;
        free(temp);
        return 1;
    }

    for(No *aux = lista->cabeca; aux != NULL; aux = aux->proximo){
        if(aux->data.ind == data){
            temp = aux;
            break;
        }
    }

    if(temp){
        temp->anterior->proximo = temp->proximo;
        temp->proximo->anterior = temp->anterior;
        free(temp);
        return 1;
    }

    return 0;
}

static void LISTAdestroi(Lista *lista){
    if(!lista->cabeca){
        free(lista);
        return;
    }

    No *temp = lista->cabeca;
    for(No *aux = temp->proximo; aux != NULL; aux = aux->proximo){
        free(temp);
        temp = aux;
    }
    free(lista);
}

static int LISTAConta(Lista *lista){
    int num = 0;
    for(No *aux = lista->cabeca; aux != NULL; aux = aux->proximo){
        ++num;
    }
    return num;
}

static Item LISTAprocura(Lista *lista, int chave){
    for(No *aux = lista->cabeca; aux != NULL; aux = aux->proximo)
        if(aux->data.ind == chave) return aux->data;
    return ITEM(-1,-1);
}

static void LISTAimprime(Lista *lista){
    for(No *aux = lista->cabeca; aux != NULL; aux = aux->proximo)
        printf("(%d-%d) ", aux->data.ind, aux->data.chave);
}

static void LISTAexplora(Lista *lista, Heap *heap, int v, int *pai, int *distancia){
    for(No *aux = lista->cabeca; aux != NULL; aux = aux->proximo){
        if(HEAPtem_indice(heap, aux->data.ind) && HEAPdiminui_chave(heap, aux->data.ind, aux->data.chave + distancia[v])){
            pai[aux->data.ind] = v;
            distancia[aux->data.ind] = aux->data.chave + distancia[v];
        }
    }
}

static void LISTAempilha(Lista *lista, Pilha *pilha){
    for(No *aux = lista->cabeca; aux != NULL; aux = aux->proximo){
        PILHAinsere(pilha, aux->data.ind);
    }
}

Lista *LISTAconstroi(){
    Lista *lista = malloc(sizeof(*lista));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->insere = &LISTAinsere;
    lista->imprime = &LISTAimprime;
    lista->remove = &LISTAremove;
    lista->conta = &LISTAConta;
    lista->destroi = &LISTAdestroi;
    lista->explora = &LISTAexplora;
    lista->procura = &LISTAprocura;
    lista->empilha = &LISTAempilha;
    return lista;
}