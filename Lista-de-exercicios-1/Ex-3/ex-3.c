/*
Algoritmo para destruir as arestas de um grafo tornando-o vazio
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

void esvaziaGrafo(VERTICE *g, int V)
{
    for (int i = 0; i < V; i++)
    {
        while (g[i].inicio->prox)
        {
            NO *p = g[i].inicio->prox;
            g[i].inicio->prox = g[i].inicio->prox->prox;
            free(p);
        }
    }
}

/*
Testes:
esvaziaGrafo(g, 5);
  for (int i = 0; i < 5; i++)
    {
        NO *p = g[i].inicio->prox;
        if(g[i].inicio != NULL)
          printf("[%i] ", g[i].inicio->v);
        else{
          printf("nothing");
        }
        while (p)
        {
            printf("%i ", p->v);
            p = p->prox;
        }
        printf("\n\n");
    }

    SAÍDA ESPERADA:
    Esvaziando grafo...

[0] 

[1] 

[2] 

[3] 

[4] 
*/