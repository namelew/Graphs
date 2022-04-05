#include <stdio.h>
#include <stdlib.h>

#define TAM 8

typedef struct{
    int node;
    int deg;
    int color;
}ColorNode;

genNodeList(int graph[TAM][TAM], int list[3][TAM]){
    int degree;
    for(int i = 0; i < TAM; i++){
        degree = 0;
        for(int j = 0; j < TAM; j++){
            if(graph[i][j]){
                degree++;
            }
        }
        list[0][i] = i;
        list[1][i] = degree;
        list[2][i] = 0;
    }
}

void orderList(ColorNode *list, int left, int right){
    int i, j, x;
    int y[3][TAM];
     
    i = left;
    j = right;
    x = list[(left + right) / 2].deg;
     
    while(i <= j) {
        while(list[i].deg > x && i < right) {
            i++;
        }
        while(list[j].deg < x && j > left) {
            j--;
        }
        if(i <= j) {
            y = list[i];
            list[i] = list[j];
            list[j] = y;
            i++;
            j--;
        }
    }
    if(j > left) {
        orderList(list, left, j);
    }
    if(i < right) {
        orderList(list, i, right);
    }
}

int isColored(ColorNode *list){
    int iscolored = 1;

    for(int i = 0; i < TAM; i++){
        if(!list[i].color){
            iscolored = 0;
        }
    }
    return iscolored;
}

int neiborDyed(int node, ColorNode *list, int graph[TAM][TAM], int color){
    int resul = 1;
    for(int i = 0; i < TAM; i++){
        if(graph[node][i] && list[i].node == i){ // if(nodo existe && sua_cor != color) 
            resul = 0;
        }
    }
    return resul;
}

void dye(ColorNode *list, int graph[TAM][TAM]){
    int end = 0;

    for(int color = 1; !isColored(list); color++){
        for(int i = 0; i < TAM; i++){
            for(int j = 0; j < TAM; j++){
                if(!list[i].color && graph[i][j] && (list[j].color != color)){
                    list[i].color = color;
                }
            }
        }
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

    int listNodes[3][TAM];

    genNodeList(graphMatrix, listNodes);

    orderList(listNodes, 0, TAM - 1);

    //dye(listNodes, graphMatrix);

    for(int i = 0; i < TAM; i++){
        printf("Node: %i\nColor:%i\n---------\n", listNodes[0][i], listNodes[2][i]);
    }

    return 0;
}