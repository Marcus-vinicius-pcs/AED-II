#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;

typedef int bool;

typedef struct adj {
    int v;
    int flag;
    int pond;
    int id;
    struct adj* prox;
} NO;

typedef struct {
    NO* inicio;
} VERTICE;

void procuraSuspeitos(VERTICE* g, int V, int x){
    for(int i = 0; i < V; i++){
        NO* p = g[i].inicio;
        while(p){
            if(p->id == x)
                printf("Suspeito %i: %i\n", i+1, p->v);
            p = p->prox;
        }
    }
}