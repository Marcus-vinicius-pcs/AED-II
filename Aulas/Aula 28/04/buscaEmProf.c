#include <stdio.h>
#include <stdlib.h>

typedef struct adj
{
    int v;
    int flag;
    int pond;
    struct adj *prox;
} NO;

typedef struct
{
    NO *inicio;
} VERTICE;

// Algo do Ivandre
void buscaEmProf(VERTICE *g, int i, bool *ciclo)
{
    *ciclo = false;
    g[i].inicio->flag = 1;
    NO *p = g[i].inicio->prox;
    while (p)
    {
        if (g[p->v].inicio->flag == 1)
        {
            printf("ciclo de %i para %i\n\n", i, p->v);
            *ciclo = true;
            return;
        }
        if (g[p->v].inicio->flag == 0)
        {
            buscaEmProf(g, p->v, ciclo);
        }
        p = p->prox;
        g[i].inicio->flag = 2;
    }
}

// Algo do Norton
void visitaP(VERTICE *g, int i)
{
    g[i].inicio->flag = 1;
    NO *p = g[i].inicio->prox;
    while (p)
    {
        if (g[p->v].inicio->flag == 0)
            visitaP(g, p->v);
        p = p->prox
    }
    g[i].inicio->flag = 2;
}

void profundidade(VERTICE *g, int V)
{
    for (int i = 0; i < V; i++)
    {
        if (g[i].inicio->flag == 0)
            visitaP(g, i);
    }
}

// Algo do norton em uma só função
void buscaEmProf(VERTICE *g, int i,int V){
    for (int i = 0; i < V; i++){
        if (g[i].inicio->flag == 0){
            g[i].inicio->flag = 1;
            NO *p = g[i].inicio->prox;
            while (p){
                if (g[p->v].inicio->flag == 0)
                    buscaEmProf(g, p->v, V);
                p = p->prox
            }
            g[i].inicio->flag = 2;
        }
    }
}
