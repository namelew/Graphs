#include <stdio.h>
#include <stdlib.h>
#define TAM 8
//  Cria uma arvore spanning de um grafo interativamente, pegando o menor peso e evitando os ciclo
// passos
// 1 - Transformar matrix de insidência em lista de vertices Ok
// 2 - Ordenar areastar por peso Ok
// 3 - Criar floresta (vetor de vertices) Ok
// 4 - Implementar sub-arvores ok
// 5 - Merge das arvores ok

typedef struct vertex{
    int w;
    int o;
    int d;
    struct vertex *next;
    struct vertex *prev;
}Vertex;


typedef struct edge{
    int o;
    int d;
    struct edge *next;
    struct edge *prev;
}Edge;

typedef struct{
    Edge *head;
    Edge *tail;
}Answer;

typedef struct{
    Vertex *head;
    Vertex *tail;
} Graph;

Graph *initGraph(){
    Graph *new = malloc(sizeof(Graph));
    new->head = NULL;
    new->tail = NULL;
}

Answer *initAnswer(){
    Answer *new = malloc(sizeof(Graph));
    new->head = NULL;
    new->tail = NULL;
}

Vertex *createVertex(int w, int o, int d){
    Vertex *new = malloc(sizeof(Vertex));
    new->w = w;
    new->o = o;
    new->d = d;
    new->next = NULL;
    new->prev = NULL;
}

Edge *createEdge(int o, int d){
    Edge *new = malloc(sizeof(Edge));
    new->o = o;
    new->d = d;
    new->next = NULL;
    new->prev = NULL;
}

void insertEdge(Answer *answer, Edge *node){
    if(!answer->head && !answer->tail){
        answer->head = node;
        answer->tail = node;
    }

    answer->tail->next = node;
    node->prev = answer->tail;
    answer->tail = node;
}

void insertVertex(Graph *graph, Vertex *node){
    if(!graph->head && !graph->tail){
        graph->head = node;
        graph->tail = node;
        return;
    }

    Vertex *current  = graph->head;

    while(current->next != NULL && current->next->w < node->w){
        current = current->next;
    }

    node->next = current->next;
    node->prev = current;
    current->next = node;
}

void *buildVexList(Graph *graph, int matrix[TAM][TAM]){
    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            if(matrix[i][j]){
                Vertex *node = createVertex(matrix[i][j], i, j);
                insertVertex(graph, node);
            }
        }
    }
}

void printAnswer(Answer *answer){
    for(Edge *aux = answer->head; aux != NULL; aux = aux->next){
        printf("(%i, %i) ", aux->o, aux->d);
    }
    printf("\n");
}

void initTrees(int *trees){
    for(int i = 0; i < TAM; i++){
        trees[i] = -1;
    }
}

int subTree(int *tree, int node){
    if(tree[node] < 0){
        return node;
    }
    subTree(tree, tree[node]);
}

void buildAswer(Answer *answer, Graph *graph, int *trees){
    Vertex *aux = graph->head;
    Edge *node;
    for(int i = 0; i < TAM-1; i++){
        printf("Explorando nodo: %i\n", i);

        int subo = subTree(trees, aux->o);
        int subd = subTree(trees, aux->d);

        if(subo != subd){
            if((trees[subo] * -1) > (trees[subd] * -1)){
                trees[aux->o] += trees[aux->d];
                trees[aux->d] = aux->o;
            } else{
                trees[aux->d] += trees[aux->o];
                trees[aux->o] = aux->d;
            }
            node = createEdge(aux->o, aux->d);
            insertEdge(answer, node);
        }
        aux = aux->next;
    }
}

int main(){
    int graphMatrix[TAM][TAM] = {
        {0, 1, 0, 3, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 7, 4, 0},
        {0, 0, 0, 0, 3, 7, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 3, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 8, 0, 0}
    };
    Graph *graph = initGraph();
    int trees[TAM];
    Answer *answer = initAnswer();

    buildVexList(graph, graphMatrix);
    initTrees(trees);

    buildAswer(answer, graph, trees);

    printAnswer(answer);

    for(int i = 0; i < TAM; i++){
        printf("Nodo: %i\n Filho/Sub-arvore:%i\n", i, trees[i]);
    }

    return 0;
}