#include "pilha.h"
#include <stdio.h>

void push(Queue *queue, int data){
    Node *new = malloc(sizeof(Node));
    Register reg;
    reg.value = data;

    new->data = reg;
    new->next = NULL;
    if(!queue->top){
        queue->top = new;
        return;
    }
    new->next = queue->top;
    queue->top = new;
}

Register pop(Node *top){
    Register aux;
    Node *temp;
    aux.value = -1;
    if(!top)
        return aux;
    aux = top->data;
    temp = top;
    top = top->next;
    free(temp);
    return aux;
}

void queueFree(Queue *queue){
    Node *aux = queue->top;
    for(Node *temp = aux->next; temp != NULL; temp = temp->next){
        free(aux);
        aux = temp;
    }
    free(queue);
}

void list(Node *top){
    if(!top)
        return;
    for(Node *aux = top; aux != NULL; aux = aux->next)
        printf("%d ", aux->data);
    printf("\n");
}

Queue *queueInit(){
    Queue *new = malloc(sizeof(Queue));
    new->top = NULL;
    new->free = &queueFree;
    new->pop = &pop;
    new->push = &push;
    new->list = &list;
    return new;
}