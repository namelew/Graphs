/*
 * Tarefa de laboratorio 00_a - Pilha
 *
 * GEN254 - Grafos - 2022/2
 *
 * Nome:      XXXX
 * Matricula: XXXX
 */

#ifndef PILHA_H

#define PILHA_H

#include <stdbool.h>
#include "item.h"

typedef struct pilha Pilha;

Pilha *PILHAconstroi();

bool PILHAvazia(Pilha *p);

void PILHAinsere(Pilha *p, Item i);

Item PILHAremove(Pilha *p);

void PILHAdestroi(Pilha *p);

#endif /* PILHA_H */
