#include <stdio.h>
#include <stdlib.h>

#define TAM 6

typedef struct{
    int value;
    int parent;
    int color;
}Paths;

void init(Paths *paths){
    for(int i=0; i<TAM; i++){
        paths[i].value = 0;
        paths[i].parent = -1;
        paths[i].color = 0;
    }
}

void dfs(int g[TAM][TAM], Paths *path,int node){
    int i;
    printf("Explorando %d\n", node);
    for(i = 0; i < TAM; i++){
        path[node].color = 1;
        if(g[node][i] && !path[i].color){
            path[i].parent = node;
            path[i].value = path[node].value + 1;
            dfs(g, path, i);
        }
        path[node].color = 2;
    }
    printf("Explorados:\n");
    for(i = 0; i < TAM; i++){
        if(path[i].color == 2){
            printf("%d(%d) ", i, path[i].value);
        }
    }
    printf("\nNão visitados:\n");
    for(i = 0; i < TAM; i++){
        if(!path[i].color){
            printf("%d(infinito) ", i);
        }
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

    Paths paths[TAM];

    init(paths);

    dfs(graph, paths, 5);
    printf("           Caminho Final\n| Vertice | Distancia | Anterior |\n");
    for(int i = 0; i < TAM; i++){
        printf("|    %i    |     %i     |     %i    |\n",i, paths[i].value, paths[i].parent);
    }

    return 0;
}