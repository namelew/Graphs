# include <stdio.h>
# include <stdlib.h>

#define TAM 5

void percorre(int g[TAM][TAM], int *vet, int o){
    vet[o]++;

    for(int i = 0; i < TAM; i++){
        if(!vet[i] && g[o][i]){
            percorre(g, vet, i);
        }
    }
}

int isConec(int g[TAM][TAM], int o){
    int *vet = calloc(sizeof(int), TAM);
    int r = 0;

    percorre(g, vet, o);

    for(int i = 0; i < TAM; i++){
        r += vet[i];
    }
    printf("%i\n", r);
    if(r - TAM){
        return 0;
    }
    return 1;
}

int main(){
    int graph[TAM][TAM] = {
        {0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}
    };

    if(isConec(graph, 0)){
        printf("Eh conexo\n");
    }else{
        printf("Nao eh conexo\n");
    }

    return 0;
}