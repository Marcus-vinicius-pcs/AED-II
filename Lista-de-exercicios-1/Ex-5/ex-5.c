/*
Recebe uma matriz e retorna uma lista de adjacencia
*/

#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;
typedef int bool;

typedef struct adj {
    int v;
    struct adj* prox;
} NO;

typedef struct{
    NO* inicio;
} VERTICE;

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

int** inicializaMatriz(int V){
    int m[V][V];
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            m[i][j] = 0;
        }
    }
    return m;
}

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