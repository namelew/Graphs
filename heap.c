#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include "item.h"

struct heap {
    Item *itens;
    int *ind_posfila;
    int max_num_itens;
    int num_itens;
};

static bool indice_valido(Heap *f, int ind) {
    if ((ind >= 0) && (ind <= (f->max_num_itens - 1))) {
        return true;
    }

    return false;
}

static int pai(int i) {
    return ((i - 1) / 2);
}

static int filho_esq(int i) {
    return ((2 * i) + 1);
}

static int filho_dir(int i) {
    return ((2 * i) + 2);
}

static void troca(Heap *f, int i, int j) {
    Item aux = f->itens[i];
    f->itens[i] = f->itens[j];
    f->itens[j] = aux;

    f->ind_posfila[f->itens[i].ind] = i;
    f->ind_posfila[f->itens[j].ind] = j;
}

static void consertaParaCima(Heap *f, int i) {
    while (i > 0) {
        if (ITEMcompara(f->itens[i], f->itens[pai(i)]) >= 0) {
            break;
        }

        troca(f, i, pai(i));

        i = pai(i);
    }
}

static void consertaParaBaixo(Heap *f, int i) {
    int menor_filho;

    while (filho_esq(i) < f->num_itens) {
        menor_filho = filho_esq(i);
        if (filho_dir(i) < f->num_itens) {
            if (ITEMcompara(f->itens[filho_dir(i)], f->itens[filho_esq(i)])
                    < 0) {
                menor_filho = filho_dir(i);
            }
        }

        if (ITEMcompara(f->itens[i], f->itens[menor_filho]) <= 0) {
            break;
        }

        troca(f, i, menor_filho);

        i = menor_filho;
    }
}

Heap *HEAPconstroi(int max_num_itens) {
    Heap *f;

    f = malloc(sizeof(*f));

    f->itens = malloc(max_num_itens * sizeof(*(f->itens)));

    f->ind_posfila = malloc(max_num_itens * sizeof(*(f->ind_posfila)));
    for (int i = 0; i < max_num_itens; i++) {
        f->ind_posfila[i] = -1;
    }

    f->max_num_itens = max_num_itens;
    f->num_itens = 0;

    return f;
}

bool HEAPvazia(Heap *f) {
    return (f->num_itens == 0);
}

bool HEAPcheia(Heap *f) {
    return (f->num_itens == f->max_num_itens);
}

bool HEAPtem_indice(Heap *f, int ind) {
    if (!indice_valido(f, ind)) {
        printf("Erro na operacao HEAPtem_indice: o indice %d eh "
            "invalido!\n", ind);
        exit(EXIT_FAILURE);
    }

    return (f->ind_posfila[ind] != -1);
}

void HEAPinsere(Heap *f, Item i) {
    if (HEAPcheia(f)) {
        printf("Erro na operacao HEAPinsere: fila de prioridade "
            "cheia!\n");
        exit(EXIT_FAILURE);
    }

    if (!indice_valido(f, i.ind)) {
        printf("Erro na operacao HEAPinsere: o indice %d do item eh "
            "invalido!\n", i.ind);
        exit(EXIT_FAILURE);
    }

    if (HEAPtem_indice(f, i.ind)) {
        printf("Erro na operacao HEAPinsere: o indice %d do item ja "
            "existe na fila de prioridade!\n", i.ind);
        exit(EXIT_FAILURE);
    }

    f->itens[f->num_itens] = i;
    f->ind_posfila[i.ind] = f->num_itens;
    f->num_itens++;

    consertaParaCima(f, (f->num_itens - 1));
}

Item HEAPremove(Heap *f) {
    Item i;

    if (HEAPvazia(f)) {
        printf("Erro na operacao HEAPremove: fila de prioridade "
            "vazia!\n");
        exit(EXIT_FAILURE);
    }

    i = f->itens[0];

    f->ind_posfila[f->itens[0].ind] = -1;

    f->itens[0] = f->itens[f->num_itens - 1];
    f->ind_posfila[f->itens[0].ind] = 0;

    f->num_itens--;

    consertaParaBaixo(f, 0);

    return i;
}

Chave HEAPchave(Heap *f, int ind) {
    if (!indice_valido(f, ind)) {
        printf("Erro na operacao HEAPchave: o indice %d eh invalido!"
            "\n", ind);
        exit(EXIT_FAILURE);
    }

    if (!HEAPtem_indice(f, ind)) {
        printf("Erro na operacao HEAPchave: o indice %d nao existe na "
            "fila de prioridade!\n", ind);
        exit(EXIT_FAILURE);
    }

    return f->itens[f->ind_posfila[ind]].chave;
}

int HEAPdiminui_chave(Heap *f, int ind, Chave c) {
    if (!indice_valido(f, ind)) {
        printf("Erro na operacao HEAPdiminui_chave: o indice %d eh "
            "invalido!\n", ind);
        exit(EXIT_FAILURE);
    }

    if (!HEAPtem_indice(f, ind)) {
        printf("Erro na operacao HEAPdiminui_chave: o indice %d nao "
            "existe na fila de prioridade!\n", ind);
        exit(EXIT_FAILURE);
    }

    if(f->itens[f->ind_posfila[ind]].chave <= c) return 0;

    f->itens[f->ind_posfila[ind]].chave = c;

    consertaParaCima(f, f->ind_posfila[ind]);

    return 1;
}

void HEAPdestroi(Heap *f) {
    free(f->itens);
    free(f->ind_posfila);

    free(f);
}
