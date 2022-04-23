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

void esvaziaGrafo(VERTICE* g, int V){
    for(int i = 0; i < V; i++){
        while(g[i].inicio->prox){
            NO* p = g[i].inicio->prox;
            g[i].inicio->prox = g[i].inicio->prox->prox;
            free(p);
        }
    }
}

VERTICE* grafoTransposto(VERTICE* g, int V){
    VERTICE* resp = inicializaGrafo(V);
    for(int i = 0; i < V; i++){
        NO* p = g[i].inicio->prox;
        while(p){
            insereAresta(resp, p->v, i);
            p = p->prox;
        }
    }
    return resp;
}
/*
int** inicializaMatriz(int V){
    int m[V][V];
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            m[i][j] = 0;
        }
    }
    return m;
}
*/
VERTICE* converteMatriz(int m[][5] , int V){
    VERTICE* g = inicializaGrafo(V);
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if(m[i][j] == 1){
                insereAresta(g, i, j);
            }
        }
    }
    return g;
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

  VERTICE *gt = grafoTransposto(g, 5);
  printf("Grafo transposto\n\n");
  for (int i = 0; i < 5; i++)
    {
        NO *p = gt[i].inicio->prox;
        printf("[%i] ", gt[i].inicio->v);
        while (p)
        {
            printf("%i ", p->v);
            p = p->prox;
        }
        printf("\n\n");
    }

  int m[5][5];
  m[0][0] = 1;
  m[0][1] = 0;
  m[0][2] = 0;
  m[0][3] = 0;
  m[0][4] = 1;
  m[1][0] = 0;
  m[1][1] = 0;
  m[1][2] = 0;
  m[1][3] = 0;
  m[1][4] = 1;
  m[2][0] = 1;
  m[2][1] = 1;
  m[2][2] = 0;
  m[2][3] = 0;
  m[2][4] = 1;
  m[3][0] = 0;
  m[3][1] = 0;
  m[3][2] = 0;
  m[3][3] = 0;
  m[3][4] = 1;
  m[4][0] = 1;
  m[4][1] = 1;
  m[4][2] = 1;
  m[4][3] = 0;
  m[4][4] = 0;

  VERTICE* gm = converteMatriz(m, 5);

  printf("Convertido de matriz\n\n");

  for (int i = 0; i < 5; i++)
    {
        NO *p = gm[i].inicio->prox;
        printf("[%i] ", gm[i].inicio->v);
        while (p)
        {
            printf("%i ", p->v);
            p = p->prox;
        }
        printf("\n\n");
    }
   
   bool achou = false;
  existeCaminho(g, 5, 0, 2, &achou);
  if(achou) printf("Ok\n\n");
  else printf("NOT FOUND\n\n");



for(int i = 0; i<5; i++){
  NO* p = g[i].inicio->prox;
  g[i].inicio->flag = 0;
  while(p){
    p->flag = 0;
    p = p->prox;
  }
}

  if(arvoreEnraizada(g, 5)) printf("Graças a Deus\n");
  else printf("Here we go again\n");

  return 0;
}