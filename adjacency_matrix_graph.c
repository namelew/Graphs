/*
Nos mesmo moldes to trabalho anterior, neste você deve implementar um grafo para imprimir as informações dos vértices. 
A ideia agora é implementar o grafo utilizando uma matriz de adjacência.

Da mesma forma que o trabalho anterior, o programa deve permitir armazenar um grafo regular ou um grafo dirigido. Esse
grafo pode ter ou não peso em suas arestas (grafo valorado). Seu programa deve calcular o  grau de um nodo X. Caso o
grafo serja orientado, o programa deve calcular: o grau de entrada e de saída de um nodo, e apresentar um conjunto de
nodos fonte e sumidouro.
*/

/*
        1    2    3   4   5
    1   0    1    1   0   0
    2   0    0    0   1   1
    3   0    1    0   0   0
    4   0    0    1   0   1
    5   0    0    0   0   0
*/

# include <stdio.h>
# include <stdlib.h>

#define SIZE 5

int vertexDegree(int graph[SIZE][SIZE], int key){
    int count = 0, i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            if(graph[i][j] && (key == i || j == key)){
                count++;
            }
        }
    }
    return count;
}

int vertexDegreeOriented(int graph[SIZE][SIZE], int key, int type){
    // type == 1 SAIDA
    // type == 0 ENTRADA
    int counts = 0, i, j, counte = 0;
    for(i = 0; i < SIZE; i++){
        counts += graph[key][i];
        counte += graph[i][key];

    }
    if(type){
        return counts;
    }
    return counte;
}

void printNoOriented(int graph[SIZE][SIZE]){
    int i, j;
    printf("\n********* Vertexes ************\n");
    for(i = 0; i < SIZE; i++){
        printf("\t %d (%d),", i+1, vertexDegree(graph, i));            
    }
    printf("\n\n********* Edges ************\n");
    for(i = 0; i < SIZE; i++){
        for(j=0; j < SIZE; j++){
            if(graph[i][j]){
                printf("\t (%d, %d)", i+1, j+1);
            }
        }            
    }
    printf("\n");
}

void printOriented(int graph[SIZE][SIZE]){
    int i, j;
    printf("\n********* Vertexes ************\n");
    for(i = 0; i < SIZE; i++){
        printf("\t%d(%d, %d)", i+1, vertexDegreeOriented(graph, i, 1), vertexDegreeOriented(graph, i, 0));            
    }
    printf("\n\n********* Edges ************\n");
    for(i = 0; i < SIZE; i++){
        for(j=0; j < SIZE; j++){
            if(graph[i][j] == 1){
                printf("\t (%d, %d)", i+1, j+1);
            }
        }
    }
    printf("\n\n********* Vertices Fonte ************\n");
    int is = 1;
    for(i = 0; i < SIZE; i++){
        for(j=0; j < SIZE; j++){
            if(graph[j][i] == 1){
                is = 0;
            }
        }
        if(is){
            printf("\t %d", i+1);
        }
        is = 1;
    }
    printf("\n\n********* Vertices Sumidouro ************\n");
    for(i = 0; i < SIZE; i++){
        for(j=0; j < SIZE; j++){
            if(graph[i][j] == 1){
                is = 0;
            }
        }
        if(is){
            printf("\t %d", i+1);
        }
        is = 1;
    }
    printf("\n");
}

int main(){
    int am[SIZE][SIZE] = {
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0}
    };

    printOriented(am);
}