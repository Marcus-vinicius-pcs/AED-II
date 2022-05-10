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
    int i;
    for (i = 0; i < V; i++)
        g[i].inicio = NULL;
    return g;
}


//Verifica se há uma aresta direta entre a e b
bool verificaAresta(VERTICE* g, int a, int b){
    NO* p = g[a].inicio->prox;
    while(p){
        if(p->v == b)
            return true;
        p = p->prox;
    }
    return false;
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

VERTICE* retornaComplemento(VERTICE* g, int V){
    VERTICE* gc = inicializaGrafo(V);
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(!verificaAresta(g, i, j))
                insereAresta(g,c i, j);
        }
    }
    return gc;
}

//pendente teste