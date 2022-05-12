#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;
typedef int bool;

typedef struct adj {
    int flag;
    int dist;
    int via;
    int v;
    struct adj* prox;
} NO;

typedef struct {
    NO* inicio;
    int Numvertices;
} VERTICE;

void buscaEmLargura(VERTICE* g, int i, int t){
    FILA f;
    inicializarFila(&f);
    g[i].inicio->flag = 1;
    entrarfila(&f, i);
    while(f.inicio){
        int j = sairfila(&f);
        NO* p = g[j].inicio->prox;
        while(p){
            if(g[p->v].inicio->flag = 0){
                g[p->v].inicio->flag = 1;
                entrarfila(&f, p->v);
                g[p->v].inicio->via = j;
                g[p->v].inicio->dist = g[j].inicio->dist + 1;
                if(p->v == t)
                    return;
            }
            p = p->prox;
        }
    }
}

void caminhoMaisCurto(VERTICE* g, int i){
    for(int j = 0; j < g->Numvertices; j++){
        buscaEmLargura(g, i, j);
    }
}

//pendente teste