#include "pilha.h"
#include <stdio.h>

int main(){
    int n,entry;
    Queue *queue = queueInit();
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &entry);
        if(entry != -1){
            queue->push(queue, entry);
        }else{
            Register temp = queue->pop(queue->top);
            if (temp.value != -1){
                printf("%d\n", temp.value);
            } else{
                printf("Pilha vazia!\n");
            }
        }
    }
    queue->free(queue);
}