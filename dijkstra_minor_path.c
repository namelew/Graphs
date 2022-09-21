#include "graph.h"

int exploreNewNode(NodePath *possiblePaths){
    int menor = INT_MAX;
    int newNode;
    for(int i = 0; i < TAM; i++){
        if(!possiblePaths[i].control && possiblePaths[i].value < menor){
            menor = possiblePaths[i].value;
            newNode = i;
        }
    }
    return newNode;
}

void init(NodePath *possiblePaths){
    for(int i = 0; i < TAM; i++){
        possiblePaths[i].parent = -1;
        possiblePaths[i].value = INT_MAX;
        possiblePaths[i].control = 0;
    }
}

void minor_path(int g[TAM][TAM], int node){
    NodePath possiblePaths[TAM];

    init(possiblePaths);

    possiblePaths[node].value = 0;
    
    for(int i = 0; i < TAM-1; i++){
        int current = exploreNewNode(possiblePaths);
        possiblePaths[current].control = 1;
        printf("\nVisiting %d node\n", current);
        for(int j=0; j < TAM; j++){
            if(g[current][j]!=0 && !possiblePaths[j].control && possiblePaths[current].value != INT_MAX && (possiblePaths[current].value + g[current][j] < possiblePaths[j].value)){
                possiblePaths[j].value = possiblePaths[current].value + g[current][j];
                possiblePaths[j].parent = current;
            }
        }
        printf("Current state\n");
        printf("-------------------------\n");
        printf("| Node | Parent | Value |\n");
        for(int i = 0; i < TAM; i++)
            printf("|   %i  |    %i   |   %i   |\n", i, possiblePaths[i].parent, possiblePaths[i].value);
        printf("-------------------------\n");
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

    printf("Primeira aresta a ser explorada?\n");

    int firstNode;
    scanf("%d", &firstNode);

    minor_path(graph, firstNode);
}