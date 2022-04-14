/*
Algoritmo que conta o número de laços em um grafo
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

// vertices
typedef struct
{
    int info;
    NO *inicio;
} VERTICE;

int contaLacos(VERTICE *g, int V)
{
    int resp = 0;
    for (int i = 0; i < V; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            if (i == p->v)
                resp++;
            p = p->prox;
        }
    }
    return resp;
}

NO *buscaAresta(VERTICE *g, int i, int j, NO **ant)
{
    NO *p = g[i].inicio;
    while (p)
    {
        if (p->v == j)
        {
            return p;
        }
        *ant = p;
        p = p->prox;
    }
    return NULL;
}

bool insereAresta(VERTICE *g, int i, int j)
{
    NO *ant;
    NO *atual = buscaAresta(g, i, j, &ant);
    if (atual)
        return false;
    atual = (NO *)malloc(sizeof(NO));
    atual->v = j;
    atual->prox = g[i].inicio;
    g[i].inicio = atual;
    return true;
}

VERTICE *inicializaGrafo(int V)
{
    VERTICE *g = (VERTICE *)malloc(sizeof(VERTICE) * V);
    int i;
    for (i = 0; i < V; i++)
        g[i].inicio = NULL;
    return g;
}

int main()
{
    VERTICE *g = inicializaGrafo(5);
    insereAresta(g, 0, 2);
    insereAresta(g, 0, 3);
    insereAresta(g, 0, 0);
    insereAresta(g, 1, 2);
    insereAresta(g, 1, 3);
    insereAresta(g, 2, 2);
    insereAresta(g, 2, 3);
    insereAresta(g, 3, 3);
    NO *tst = (NO *)malloc(sizeof(NO));
    printf("%i ", contaLacos(g, 5));
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        NO *p = g[i].inicio;
        while (p)
        {
            printf("%i ", p->v);
            p = p->prox;
        }
        printf("\n\n");
    }

    return 0;
}