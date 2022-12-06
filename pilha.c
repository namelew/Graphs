/*
 * Tarefa de laboratorio 00_a - Pilha
 *
 * GEN254 - Grafos - 2022/2
 *
 * Nome:      XXXX
 * Matricula: XXXX
 */

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct elemPilha {
    int item;
    struct elemPilha *proximo;
};
typedef struct elemPilha ElemPilha;

struct pilha {
    ElemPilha *topo;
};

Pilha *PILHAconstroi() {
    Pilha *p;

    p = malloc(sizeof(*p));
    p->topo = NULL;

    return p;
}

bool PILHAvazia(Pilha *p) {
    return (p->topo == NULL);
}

void PILHAinsere(Pilha *p, int i) {
    ElemPilha *aux;

    // Cria um novo elemento da lista encadeada que representa a pilha e
    // armazena neste novo elemento o item a ser inserido na pilha
    aux = malloc(sizeof(*aux));
    aux->item = i;

    // Insere o novo elemento no inicio da lista encadeada que representa a
    // pilha
    aux->proximo = p->topo;
    p->topo = aux;
}

int PILHAremove(Pilha *p) {
    int i;
    ElemPilha *aux;

    if (PILHAvazia(p)) {
        printf("Erro na operacao PILHAremove: pilha vazia!\n");
        exit(EXIT_FAILURE);
    }

    // Armazena o item a ser removido da pilha
    i = p->topo->item;

    // Armazena o primeiro elemento da lista encadeada que representa a pilha
    // e remove este primeiro elemento da lista
    aux = p->topo;
    p->topo = p->topo->proximo;

    // Libera a memoria alocada para o elemento removido
    free(aux);

    // Retorna o item removido da pilha
    return i;
}

void PILHAdestroi(Pilha *p) {
    ElemPilha *aux;

    while (!PILHAvazia(p)) {
        // Armazena o primeiro elemento da lista encadeada que representa a
        // pilha e remove este primeiro elemento da lista
        aux = p->topo;
        p->topo = p->topo->proximo;

        // Libera a memoria alocada para o elemento removido
        free(aux);
    }

    free(p);
}
