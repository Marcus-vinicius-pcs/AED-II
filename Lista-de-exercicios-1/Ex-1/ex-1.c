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

void insereAresta(VERTICE *g, int i, int j)
{
    NO *atual = (NO *)malloc(sizeof(NO));
    atual->v = j;
    atual->prox = g[i].inicio;
    g[i].inicio = atual;
}

VERTICE *inicializaGrafo(int V)
{
    VERTICE *g = (VERTICE*) malloc(sizeof(VERTICE) * V);
    int i;
    for (i = 0; i < V; i++)
        g[i].inicio = NULL;
    return g;
}

int main()
{
    VERTICE *g = inicializaGrafo(5);
    for (int i = 0; i < 5; i++)
    {
        insereAresta(g, i, i);
    }
    printf("%i ", contaLacos(g, 5));
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%i ", g[i].inicio->v);
    }
    return 0;
}