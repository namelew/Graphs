#include<stdio.h>
#include<stdlib.h>

/*
 Vertex linked list
*/
struct _vertex {
    int value;
    struct _vertex *next;
};
typedef struct _vertex Vertex;

/*
 Edge linked list
*/

struct _edge {
    Vertex *s;
    Vertex *d;
    struct _edge *next;
};
typedef struct _edge Edge;

typedef struct {
    int oriented;
    Vertex *vertexes; //primeiro elemento da lista de vértices
    Edge *edges; //primeiro elemento da lista de arestas
} Graph;

Vertex *insertVertex(Vertex *head, int value){
    Vertex *new = malloc (sizeof(Vertex));
    new->value = value;

    new->next = head;

    return new;
}

int vertexDegree(Edge *head,int v){
    int count = 0;
    Edge *aux;
    for(aux = head; aux != NULL; aux=aux->next){
        if(aux->d->value == v || aux->s->value == v){
            count++;
        }
    }
    return count;
    
}

int vertexDegreeOriented(Edge *head, int v, int type){
    int count = 0;
    Edge *aux;
    for(aux = head; aux != NULL; aux=aux->next){
        if(aux->d->value == v && !type){
            count++;
        }
        if(aux->s->value == v && type){
            count++;
        }
    }
    return count;
}

//Exemplo de print
void printGraphNotOriented( Graph *graph){
    Vertex *auxV;
    Edge *auxE;
    printf("\n********* Vertexes ************\n");
    for (auxV = graph->vertexes; auxV!=NULL; auxV=auxV->next) 
        printf("\t %d (%d),", auxV->value, vertexDegree(graph->edges, auxV->value));
    
    printf("\n\n********* Edges ************\n");
    if (graph->edges == NULL)
      printf("No edges!");
    else
        for (auxE = graph->edges; auxE!=NULL; auxE=auxE->next) 
            printf("\t (%d, %d)", auxE->s->value, auxE->d->value);
        
    printf("\n");
}

//Exemplo de print
void printGraphOriented( Graph *graph){
    Vertex *auxV;
    Edge *auxE;
    printf("\n********* Vertexes ************\n");
    for (auxV = graph->vertexes; auxV!=NULL; auxV=auxV->next) 
        printf("\t %d s(%d) e(%d),\n", auxV->value, vertexDegreeOriented(graph->edges, auxV->value, 1), vertexDegreeOriented(graph->edges, auxV->value, 0));
    
    printf("\n\n********* Edges ************\n");
    if (graph->edges == NULL)
      printf("No edges!");
    else
        for (auxE = graph->edges; auxE!=NULL; auxE=auxE->next) 
            printf("\t (%d, %d)", auxE->s->value, auxE->d->value);

    printf("\n\n********* Vertices Fonte ************\n");

    printf("\n\n********* Vertices Sumidouro ************\n");
        
    printf("\n");
}

//insertEdge(*Graph, int v_origem, int v_destino)
    // Buescar a Origem e o Destino na lista de Vértices. 
       //Devem ser os mesmo que estão na lista de vértices, não podem ser criados.
Edge *insertEdge(Graph *g, int v_origem, int v_destino){
    Vertex *temp1 = NULL, *temp2 = NULL;
    for(Vertex *aux = g->vertexes;aux != NULL && (temp1 == NULL || temp2 == NULL);aux = aux->next){
        if(aux->value == v_origem && temp1 == NULL){
            temp1 = aux;
        }
        if(aux->value == v_destino && temp2 == NULL){
            temp2 = aux;
        }
    }
    if(temp1 != NULL && temp2 != NULL){
        Edge *new = malloc(sizeof(Edge));
        new->s = temp1;
        new->d = temp2;
        new->next = g->edges;
        return new;
    }
    return g->edges;
}

//Não orientado:
// -- Listar todos os vertices com os respectivos graus.

//Grafo orientado:
// -- Listar os graus de entrada e saida para cada um dos vértices.
// -- Listar todos os vértices que são sumidouro
// -- Listar todos os vértices que são fonte

Graph *newGraph(int o){
    Graph *new = malloc (sizeof(Graph));
    
    //não orientado = 0
    //orientado = 1

    new->oriented = o;
    
    new->edges = NULL;
    new->vertexes = NULL;
    return new;
}

int main(){

    Graph *g1 = newGraph(0);

    g1->vertexes = insertVertex(g1->vertexes, 1);
    g1->vertexes = insertVertex(g1->vertexes, 2);
    g1->vertexes = insertVertex(g1->vertexes, 3);
    g1->vertexes = insertVertex(g1->vertexes, 4);
    g1->vertexes = insertVertex(g1->vertexes, 5); 

    g1->edges = insertEdge(g1, 5, 1);
    g1->edges = insertEdge(g1, 5, 2);
    g1->edges = insertEdge(g1, 5, 3);
    g1->edges = insertEdge(g1, 5, 4);   

    printGraphNotOriented(g1);
    printGraphOriented(g1);


    return 0;
}