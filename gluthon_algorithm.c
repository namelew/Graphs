/*
T3 - Algoritmo Guloso

Implementar um algoritmo guloso em C que tenta achar um caminho entre dois nodos através de uma matriz de adjacência.
O algoritmo pode não achar um caminho, mesmo que esse exista:

    se chegar em um ponto onde não consegue mais avançar deve retornar "Impossível com Guloso"
    Se fizer mais que N passos e não encontrar o caminho imprimir "Cansei, impossível fazer com Guloso".
    Verificar se a melhor opção não para o mesmo nodo, se for, pega a segunda melhor (Evita loops).
*/
# include <stdio.h>
# include <stdlib.h>

# define SIZE 5

void gluthon_algorithm(int graph[SIZE][SIZE], int init, int end){ // tá percorrendo mas não tá fazendo a lógica do guloso
    if(graph[init][end]){
        printf("%d -> %d (%d)\n", init+1, end+1, graph[init][end]);
        return;
    }
    int i, path = 0;
    for(i = 0; i < SIZE; i++){
        if(graph[init][i]){
            printf("%d -> %d\n", init+1, i+1);
            if(graph[i][end]){
                printf("%d -> %d\n", i+1, end+1);
                break;
            }else{
                continue;
            }
        }
    }
    if(i == SIZE){
        printf("Cansei, impossivel fazer com Guloso");
    }
}

int main(){
    int am[SIZE][SIZE] = {
        {0, 1, 1, 0, 0}, // a r+(b, c, d, e) r-()
        {0, 0, 0, 1, 1}, // b r+(b, c, d, e) r-(a, c, d)
        {0, 1, 0, 0, 0}, // c r+(b, c, d, e) r-(a, b, d)
        {0, 0, 1, 0, 1}, // d r+(b, c, d, e) r-(a, b, c)
        {0, 0, 0, 0, 0}  // e r+() r-(a, b, c, d)
    };
    int init, end;
    printf("Path(init end): ");
    scanf("%d %d", &init, &end);

    gluthon_algorithm(am, init-1, end-1);

    return 0;
}