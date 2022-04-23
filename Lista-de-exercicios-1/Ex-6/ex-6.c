/*
verifica se o grafo é uma árvore enraizada ou não
*/

#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;

typedef int bool;

typedef struct adj {
    int v;
    int flag;
    struct adj* prox;
} NO;

typedef struct {
    NO* inicio;
} VERTICE;

void existeCaminho(VERTICE* g, int V,int v1, int v2, bool* achou){
  g[v1].inicio->flag = 1;
  if(v1 == v2) {
    *achou = true;
    return;
  }
  NO* p = g[v1].inicio->prox;
  while(p){
    if((g[p->v].inicio->flag == 0) && (!*achou)){
      existeCaminho(g, V, p->v, v2, achou);
    } p = p->prox;
  } g[v1].inicio->flag = 2;
}

int grauDeEntrada(VERTICE* g, int V,int i){
    int resp = 0;
    for(int j = 0; j < V; j++){
        NO* p = g[j].inicio->prox;
        while(p){
            if(p->v == i)
                resp++;
            p = p->prox;
        }
    }
    return resp;
}

//grau de entrada deve ser 0 para que um vertice seja considerado raiz


void buscaEmProf(VERTICE* g, int i, bool* ciclo){
    *ciclo = false;
    g[i].inicio->flag = 1;
    NO* p = g[i].inicio->prox;
    while(p){
        if(g[p->v].inicio->flag == 1){
            printf("ciclo de %i para %i\n\n", i, p->v);
            *ciclo = true;
            return;
        }
        if(g[p->v].inicio->flag == 0){
            buscaEmProf(g, p->v, ciclo);
        }
        p = p->prox;
        g[i].inicio->flag = 2;
    }
}

NO* encontraRaiz(VERTICE* g, int V){
    for(int i = 0; i < V; i++){
        NO* p = g[i].inicio;
        int grau = 0;
        while(p){
            grau = grauDeEntrada(g, V, p->v);
            if(grau == 0)
                return p;
            else 
                p = p->prox;
        }
    }
    return NULL;
}

bool arvoreEnraizada(VERTICE* g, int V){
    bool ciclo;
    bool achou;

    //Verifica se é acíclico
    buscaEmProf(g, 0, &ciclo);
    if(ciclo) return false;

    //Verifica se possui uma raiz
    NO* raiz = encontraRaiz(g, V);
    if(raiz == NULL) return false;
    
    //Verifica se é conexo
    for(int i = 0; i < V; i++){
        existeCaminho(g, V, raiz->v, i, &achou);
        if(!achou)
            return false;
    }

    return true;

}