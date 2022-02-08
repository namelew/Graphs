#include <stdio.h>
#include <stdlib.h>

#define TAM 6
#define INT_MAX 2147483647

typedef struct node{
    int value;
    struct node *next;
}Node;

typedef struct{
    Node *top;
    Node *tail;
}Queue;

typedef struct{
    int value;
    int parent;
    int color;
}Paths;

void initQueue(Queue *queue){
    queue->top = NULL;
    queue->tail = NULL;
}

void initPaths(Paths *paths){
    for(int i=0; i < TAM; i++){
        paths[i].color = 0;
        paths[i].value = INT_MAX;
        paths[i].parent = -1;
    }
} 

void push(Queue *queue, int value){
    Node *new = malloc(sizeof(Node));
    new->value = value;
    new->next = NULL;

    if(!queue->tail){
        queue->tail = new;
        queue->top = new;
        return;
    }

    queue->tail->next = new;
    queue->tail = new;
}

int pop(Queue *queue){
    if(!queue->tail){
        return;
    }
    Node *aux = queue->top;
    int value = aux->value;
    if(queue->top == queue->tail){
        free(aux);
        queue->top = NULL;
        queue->tail = NULL;
        return value;   
    }
    queue->top = queue->top->next;
    free(aux);

    return value;
}

void bfs(int g[TAM][TAM], int node){
    Queue queue;
    Paths paths[TAM];

    initQueue(&queue);
    initPaths(paths);

    paths[node].color = 1;
    paths[node].value = 0;

    push(&queue, node);

    while(queue.tail){
        int current = pop(&queue);
        printf("Explorando vertice %d\n", current);
        for(int i = 0; i < TAM; i++){
            if(g[current][i] && !paths[i].color){
                paths[i].color = 1;
                paths[i].value = paths[current].value + 1;
                paths[i].parent = current;
                push(&queue, i);
            }
        }
        paths[current].color = 2;
        printf("Totalmente Explorados: ");
        for(int i = 0; i < TAM; i++){
            if(paths[i].color == 2){
                printf("%d(%d) ", i, paths[i].value);
            }
        }
        printf("\n");

        printf("Visitados: ");
        for(int i = 0; i < TAM; i++){
            if(paths[i].color == 1){
                printf("%d(%d) ", i, paths[i].value);
            }
        }
        printf("\n");

        printf("Nao Explorados: ");
        for(int i = 0; i < TAM; i++){
            if(!paths[i].color){
                printf("%d(infinito) ", i);
            }
        }
        printf("\n\n");
    }
    printf("-------------------------------------\n");
    for(int i = 0; i < TAM; i++){
        printf("Vertice: %d\nDistancia: %d\nAnterior: %d\n", i, paths[i].value, paths[i].parent);
        printf("-------------------------------------\n");
    }
}


int main(){
    int graph[TAM][TAM] = {
        {0,1,4,0,0,0},
        {1,0,4,2,7,0},
        {4,4,0,3,5,0},
        {0,2,3,0,4,6},
        {0,7,5,4,0,7},
        {0,0,0,6,7,0}
    };


    bfs(graph, 5);

    return 0;
}