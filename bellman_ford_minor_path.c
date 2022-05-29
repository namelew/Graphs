#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 2147483647
#define TAM 6

typedef struct{
    int distance;
    int previous;
}Node;

void init(Node *node){
    for(int i = 0; i < TAM; i++){
        node[i].distance = INT_MAX;
        node[i].previous = 0;
    }
}

Node *bellmanFord(int graph[TAM][TAM], int start){
    Node *nodes = malloc(sizeof(Node) * TAM);

    init(nodes);

    nodes[start].distance = 0;

    for(int i = 0; i < TAM; i++){
        for(int j = 0; j<TAM; j++){
            if(graph[i][j]){
                int tem = nodes[i].distance == INT_MAX ? graph[i][j] : nodes[i].distance + graph[i][j];
                if (tem < nodes[j].distance){
                    nodes[j].distance = tem;
                    nodes[j].previous = i;
                }
            }
        }
    }

    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            if (graph[i][j] && (nodes[i].distance + graph[i][j] < nodes[j].distance)){
                free(nodes);
                printf("Erro Negative Cycle Exists\n");
                return NULL;
            }
        }
    }

    return nodes;
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

    Node *result = bellmanFord(graph, 0);

    if(!result){
        printf("Can't find a minor path to the graph\n");
        exit(1);
    }

    for(int i = 0; i < TAM; i++){
        printf("Distance: %d || Previous: %d\n", result[i].distance, result[i].previous);
    }

    return 0;
}