#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;
typedef int bool;

typedef struct adj {
    int flag;
    char companhia;
    int via;
    int v;
    char cidade;
    int dist;
    struct adj* prox;
} NO;

typedef struct {
    NO* inicio;
    int Numvertices;
} VERTICE;

typedef struct {
    NO* cabeca;
} LISTA;

/*
Seja um grafo representando uma malha aérea. Vértices são cidades e arestas são voos. Escreva um
algoritmo que, dada uma cidade origem a, um destino b e uma companhia aérea c, encontre o
trajeto com menor número de conexões de a até b voando apenas pela companhia c. A resposta
deve ser fornecida na forma de uma lista ligada de vértices de a até b.
*/

LISTA* buscaLargura(VERTICE* g, int a, int b){
    FILA f;
    LISTA l;
    inicializaLista(&l);
    inicializafila(%f);
    g[a].inicio->flag = 1;
    entrarfila(&f, i);
    while(f.inicio){
        a = sairFila(&f);
        NO* p = g[a].inicio->prox;
        while(p){
            if(g[p->v].inicio->flag = 0 && p->companhia == 'c'){
                g[p->v].inicio->flag = 1;
                g[p->v].inicio->via = i;
                entrarfila(&f, p->v);
                g[p->v].inicio->dist = g[a].inicio->dist + 1;
                entrarLista(&l, p);
                if(p->cidade == b)
                    return;
            }
            p = p->prox;
        }
    }
    return l;
}