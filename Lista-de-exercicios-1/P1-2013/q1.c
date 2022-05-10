#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;
typedef int bool;

typedef struct adj {
    int v;
    int id;
    bool recebeu;
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
        p->prox = NULL;
        g[i].inicio = p;
    }
    return g;
}

bool insereAresta(VERTICE *g, int i, int j, int x)
{ /*
     NO *ant;
     NO *atual = buscaAresta(g, i, j, &ant);
     if (atual)
         return false;*/
    NO *atual = (NO *)malloc(sizeof(NO));
    atual->v = j;
    atual->id = x;
    atual->prox = g[i].inicio->prox;
    g[i].inicio->prox = atual;
    return true;
}

int spammer(VERTICE* g, int V, int x){
    int spammer = -1;
    for(int i = 0; i < V; i++){
        NO* p = g[i].inicio->prox;
        while(p){
          if(p->id == x){
              g[p->v].inicio->recebeu = true;
              if(!g[i].inicio->recebeu)
                  spammer = i;
          } p = p->prox;
        }
    }
    return spammer;
}

int main()
{
    VERTICE *g = inicializaGrafo(7);
    insereAresta(g, 0, 3, 8);
    insereAresta(g, 0, 4, 8);
    insereAresta(g, 1, 2, 9);
    insereAresta(g, 2, 3, 8);
    insereAresta(g, 2, 5, 9);
    insereAresta(g, 4, 0, 8);
    insereAresta(g, 4, 3, 8);
    insereAresta(g, 5, 4, 8);
    insereAresta(g, 6, 1, 9);

    for (int i = 0; i < 7; i++)
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
  printf("%i\n", spammer(g, 7, 9));
  return 0;
}

