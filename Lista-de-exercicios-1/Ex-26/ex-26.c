#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;
typedef int bool;

typedef struct adj {
    int flag;
    int msgs;
    int via;
    int v;
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
 Seja um grafo dirigido representando trocas de email entre usuários. Os vértices são usuários e as
arestas orientadas indicam que houve envio de mensagens na respectiva direção, incluindo um
contador do número de mensagens enviadas. Escreva um algoritmo que, dado um usuário atual i,
retorne uma lista ligada contendo todos os usuários que estão diretamente relacionados com i, e
que enviaram ou receberam pelo menos k mensagens de/para i. A constante k é fornecida como
parâmetro de entrada para a função
*/

LISTA* emailcomUser(VERTICE* g, int i, int k){
    LISTA* l;
    inicializaLista(&l); // l->cabeca = NULL;
    NO* p = g[i].inicio->prox;
    while(p){
        NO* pl = g[p->v].inicio->prox;
        while(pl){
            if(pl->v == i && pl->msgs >= k)
                inserirLista(&l, pl);
            pl = pl->prox;
        }
        if(p->msgs >= k)
            inserirLista(&l, p);
        p = p->prox;
    }
    return l;
}