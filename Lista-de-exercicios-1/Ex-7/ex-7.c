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
} VERTICE;

VERTICE *inicializaGrafo(int V)
{

    VERTICE *g = (VERTICE *)malloc(sizeof(VERTICE) * V);
    for (int i = 0; i < V; i++)
    {
        NO *p = (NO *)malloc(sizeof(NO));
        p->v = i;
        p->flag = 0;
        p->prox = NULL;
        g[i].inicio = p;
    }
    return g;
}

bool insereArestaPonderada(VERTICE *g, int i, int j, int c)
{ /*
     NO *ant;
     NO *atual = buscaAresta(g, i, j, &ant);
     if (atual)
         return false;*/
    NO *atual = (NO *)malloc(sizeof(NO));
    atual->v = j;
    atual->prox = g[i].inicio->prox;
    atual->pond = c;
    g[i].inicio->prox = atual;
    return true;
}

VERTICE* filtraAresta(VERTICE* g, int c, int V){
    VERTICE* resp = inicializarGrafo(V);
    for(int i = 0; i < V; i++){
        NO* p = g[i].inicio->prox;
        while(p){
            if(p->pond > c)
                insereArestaPonderada(resp, g[i].inicio->v, p->v, p->pond);
            p = p->prox;
        }
    }
    return resp;
}