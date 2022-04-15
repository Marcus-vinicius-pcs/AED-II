/*
Retorna o grafo transposto de g
*/
#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;
typedef int bool;

typedef struct adj
{
    int v;
    struct adj *prox;
} NO;

typedef struct
{
    NO *inicio;
} VERTICE;

VERTICE *inicializaGrafo(int V)
{
    VERTICE *g = (VERTICE *)malloc(sizeof(VERTICE));
    for (int i = 0; i < V; i++)
    {
        NO *p = (NO *)malloc(sizeof(NO));
        p->v = i;
        p->prox = NULL;
        g[i].inicio = p;
    }
    return g;
}

bool insereAresta(VERTICE *g, int i, int j)
{ /*
     NO *ant;
     NO *atual = buscaAresta(g, i, j, &ant);
     if (atual)
         return false;*/
    NO *atual = (NO *)malloc(sizeof(NO));
    atual->v = j;
    atual->prox = g[i].inicio->prox;
    g[i].inicio->prox = atual;
    return true;
}

VERTICE *grafoTransposto(VERTICE *g, int V)
{
    VERTICE *resp = inicializaGrafo(V);
    for (int i = 0; i < V; i++)
    {
        NO *p = g[i].inicio->prox;
        while (p)
        {
            insereAresta(resp, p->v, i);
            p = p->prox;
        }
    }
    return resp;
}