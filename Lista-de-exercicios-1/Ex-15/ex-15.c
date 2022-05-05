#include <stdio.h>
#include <stdlib.h>

typedef struct adj {
    int v;
    int flag;
    int pond;
    struct adj* prox;
} NO;

typedef struct {
    NO* inicio;
} VERTICE;

int contaSubgrupos(VERTICE* g, int V){
    int resp = 0;

    for(int i = 0; i < V; i++){
        if(g[i].flag == 0){
            buscaEmProf(g, i);
            resp++;
        }
    }

    return resp;
}

//pendente fazer