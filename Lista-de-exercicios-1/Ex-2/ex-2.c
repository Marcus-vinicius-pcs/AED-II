/*
Algoritmo que remove todos os laços encontrados
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

int contaLacos(VERTICE *g, int V)
{
    int resp = 0;
    for (int i = 0; i < V; i++)
    {
        NO *p = g[i].inicio->prox;
        while (p)
        {
            if (i == p->v)
                resp++;
            p = p->prox;
        }
    }
    return resp;
}

VERTICE *inicializaGrafo(int V)
{

    VERTICE *g = (VERTICE *)malloc(sizeof(VERTICE) * V);
    for (int i = 0; i < V; i++)
    {
        NO *p = (NO *)malloc(sizeof(NO));
        p->v = i;
        p->prox = NULL;
        g[i].inicio = p;
    }
    return g;
}

NO *buscaAresta(VERTICE *g, int i, int j, NO **ant)
{
    NO *p = g[i].inicio->prox;
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

bool excluirAresta(VERTICE *g, int i, int j)
{
    NO *ant;
    NO *atual = buscaAresta(g, i, j, &ant);
    if (!atual)
        return false;
    if (ant)
        ant->prox = atual->prox;
    else
        g[i].inicio = atual->prox;
    free(atual);
    return true;
}

void excluirLacos(VERTICE *g, int V)
{
    int resp = 0;
    for (int i = 0; i < V; i++)
    {
        NO *p = g[i].inicio->prox;
        while (p)
        {
            if (i == p->v)
            {
                NO *ant;
                excluirAresta(g, i, p->v);
                resp++;
            }
            p = p->prox;
        }
    }
    printf("%i laços excluídos\n\n", resp);
}

int main()
{
    VERTICE *g = inicializaGrafo(5);
    insereAresta(g, 0, 0);
    insereAresta(g, 0, 3);
    insereAresta(g, 0, 2);
    insereAresta(g, 1, 1);
    insereAresta(g, 1, 3);
    insereAresta(g, 2, 1);
    insereAresta(g, 2, 3);
    insereAresta(g, 3, 2);
    insereAresta(g, 4, 1);

    printf("%i ", contaLacos(g, 5));
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        NO *p = g[i].inicio->prox;
        printf("[%i] ", g[i].inicio->v);
        while (p)
        {
            printf("%i ", p->v);
            p = p->prox;
        }
        printf("\n\n");
    }

    excluirLacos(g, 5);

    for (int i = 0; i < 5; i++)
    {
        NO *p = g[i].inicio->prox;
        printf("[%i] ", g[i].inicio->v);
        while (p)
        {
            printf("%i ", p->v);
            p = p->prox;
        }
        printf("\n\n");
    }
    return 0;
}
