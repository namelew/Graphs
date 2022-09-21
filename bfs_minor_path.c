#include "graph.h"

typedef struct node{
    int value;
    struct node *next;
}Node;

typedef struct{
    Node *top;
    Node *tail;
}Queue;

void initQueue(Queue *queue){
    queue->top = NULL;
    queue->tail = NULL;
}

void initPaths(NodePath *paths){
    for(int i=0; i < TAM; i++){
        paths[i].control = 0;
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

    new->next = queue->top;
    queue->top = new;
}

int pop(Queue *queue){
    if(!queue->tail)
        return -1;
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

void bfs(int g[TAM][TAM], int node, int destiny){
    Queue queue;
    NodePath paths[TAM];

    initQueue(&queue);
    initPaths(paths);

    paths[node].control = 1;
    paths[node].value = 0;

    push(&queue, node);

    while(queue.tail){
        int current = pop(&queue);
        if(current == -1)
            break;
        printf("Explorando vertice %d\n", current);
        for(int i = 0; i < TAM; i++){
            if(g[current][i] && !paths[i].control){
                paths[i].control = 1;
                paths[i].value = paths[current].value + 1;
                paths[i].parent = current;
                push(&queue, i);
            }
        }
        paths[current].control = 2;
        printf("Totalmente Explorados: ");
        for(int i = 0; i < TAM; i++){
            if(paths[i].control == 2){
                printf("%d(%d) ", i, paths[i].value);
            }
        }

        printf("\nVisitados: ");
        for(int i = 0; i < TAM; i++){
            if(paths[i].control == 1){
                printf("%d(%d) ", i, paths[i].value);
            }
        }

        printf("\nNao Explorados: ");
        for(int i = 0; i < TAM; i++){
            if(!paths[i].control){
                printf("%d(infinito) ", i);
            }
        }
        printf("\n\n");

        if(current == destiny)
            break;
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

    int firstNode;
    int lastNode;

    printf("Origem: ");
    scanf("%d", &firstNode);
    printf("Destino: ");
    scanf("%d", &lastNode);

    bfs(graph, firstNode, lastNode);

    return 0;
}