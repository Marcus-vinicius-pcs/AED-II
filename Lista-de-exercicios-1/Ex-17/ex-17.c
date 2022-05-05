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

//i é o vértice a e chave é o vértice b
bool existeCaminhobuscaEmProf(VERTICE *g, int i,int V, int chave){
    for (int i = 0; i < V; i++){
        if (g[i].inicio->flag == 0){
            g[i].inicio->flag = 1;
            NO *p = g[i].inicio->prox;
            while (p){
                if(p->v == chave)
                    return true;
                if (g[p->v].inicio->flag == 0)
                    existeCaminhobuscaEmProf(g, p->v, V, chave);
                p = p->prox
            }
            g[i].inicio->flag = 2;
        }
    }
    return false;
}


//pendente teste