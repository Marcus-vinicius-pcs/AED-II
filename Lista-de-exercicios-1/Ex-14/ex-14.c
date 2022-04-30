/*
Variação 2: retornar o comprimento (i.e., a quantidade de arestas) do maior ciclo encontrado.
*/

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


void RemoveCiclos(VERTICE* g, int i, bool* ciclo){
    *ciclo = false;
    g[i].inicio->flag = 1;
    NO* p = g[i].inicio->prox;
    while(p){
        if(g[p->v].inicio->flag == 1){
            *ciclo = true;
            printf("ciclo de %i para %i", i, p->v);
            if(excluirAresta(g, i, p->v))
                printf("Aresta excluída\n");
            else 
                printf("Erro de exclusão!\n");
        }
        if(g[p->v].inicio->flag == 0){
            ContemCiclo(g, p->v, ciclo);
        }
        p = p->prox;
        g[i].inicio->flag = 2;
    }
}