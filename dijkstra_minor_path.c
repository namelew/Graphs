# include <stdio.h>
# include <stdlib.h>
# include <math.h>

#define TAM 6
#define INT_MAX 2147483647

typedef struct{
    int isVisited;
    int value;
    int before;
}NodePath;

int exploreNewNode(NodePath *possiblePaths){
    int menor = INT_MAX;
    int newNode;
    for(int i = 0; i < TAM; i++){
        if(!possiblePaths[i].isVisited && possiblePaths[i].value < menor){
            menor = possiblePaths[i].value;
            newNode = i;
        }
    }
    return newNode;
}

void init(NodePath *possiblePaths){
    for(int i = 0; i < TAM; i++){
        possiblePaths[i].before = -1;
        possiblePaths[i].value = INT_MAX;
        possiblePaths[i].isVisited = 0;
    }
}

void minor_path(int g[TAM][TAM], int node){
    NodePath possiblePaths[TAM];

    init(possiblePaths);

    possiblePaths[node].value = 0;
    
    for(int i = 0; i < TAM-1; i++){
        int current = exploreNewNode(possiblePaths);
        possiblePaths[current].isVisited = 1;

        for(int j=0; j < TAM; j++){
            if(g[current][j]!=0 && !possiblePaths[j].isVisited && possiblePaths[current].value != INT_MAX && (possiblePaths[current].value + g[current][j] < possiblePaths[j].value)){
                possiblePaths[j].value = possiblePaths[current].value + g[current][j];
                possiblePaths[j].before = current;
            }
        }
    }
    for(int i = 0; i < TAM; i++){
        printf("Node:%i\nParent: %i\nValue:%i\n", i+1, possiblePaths[i].before, possiblePaths[i].value);
        printf("-------------------------------------------------\n");
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

    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++){
            printf("%i ", graph[i][j]);
        }
        printf("\n");
    }
    printf("Primeira aresta a ser explorada?\n");

    int firstNode;
    scanf("%d", &firstNode);

    minor_path(graph, firstNode);
}