#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;
typedef int bool;

typedef struct adj {
    int flag;
    int dist;
    int via;
    int v;
    struct adj* prox;
} NO;

typedef struct {
    NO* inicio;
    int Numvertices;
} VERTICE;

/*
Seja um grafo não-dirigido representando uma rede social. Os vértices são os usuários e as arestas
indicam relações (e.g., de amizade) entre pares de usuários. Dado um usuário i, escreva um
algoritmo para exibir todos os usuários relacionados a i com até d graus de distância (medida em
quantidade de arestas). Os amigos imediatos estão no grau 1, os amigos dos amigos no grau 2, e
assim por diante
*/

void buscaEmLargura(VERTICE* g, int i){
    FILA f;
    inicializafila(&f);
    g[i].inicio->flag = 1;
    entrarFila(&f, i);
    while(f.inicio){
        i = sairFila(&f);
        NO* p = g[i].inicio->prox;
        while(p){
            if(g[p->v].inicio->flag = 0 && p->v != i){
                g[p->v].inicio->flag = 1;
                g[p->v].inicio->via = i;
                g[p->v].inicio->dist = g[i].inicio->dist + 1;
                entrarFila(&f, p->v);
            }
            p = p->prox;
        }
    }
}

void exibirAmigos(VERTICE* g, int i, int d){
    buscaEmLargura(g, i);
    printf("Amigos de %i:\n", i);
    for(int j = 0; j < g->Numvertices; j++){
        if(g[j].inicio->flag == 1 && g[j].inicio->dist <= d){
            printf("%i ", g[j].inicio->v);
        }
    }
}