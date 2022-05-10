#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;
typedef int bool;

typedef struct adj {
    int v;
    int flag;
    int pond;
    struct adj* prox;
} NO;

typedef struct {
    NO* inicio;
    int vertices;
} VERTICE;

bool ehcompleto(VERTICE* g){
    int cont;
    for(int i = 0; i < g->vertices; i++){
        cont = 0;
        NO* p = g[i].inicio->prox;
        while(p){
            cont++;
            p = p->prox
        }
        if(cont != V-1)
            return false;
    }
    return true;
}

//pendente teste
