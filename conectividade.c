# include <stdio.h>
# include <stdlib.h>

#define TAM 5

void Percorre(int g[TAM][TAM], int *vet, int o){
    vet[o]++;

    for(int i = 0; i < TAM; i++){
        if(!vet[i] && !g[o][i]){
            Percorre(g, vet, i);
        }
    }
}

int isConec(int g[TAM][TAM], int o){
    int vet[TAM], r;

    Percorre(g, vet, o);

    for(int i = 0; i < TAM; i++){
        r += vet[i];
    }
    
    if(r - TAM){
        return 0;
    }
    return 1;
}

int main(){
    int graph[TAM][TAM] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    if(isConec(graph, 0)){
        printf("Eh conexo\n");
    }else{
        printf("Nao eh conexo\n");
    }



    return 0;
}