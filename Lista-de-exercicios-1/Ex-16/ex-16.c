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

//busca em profundidade adaptada que retorna a lista de nos com o caminho percorrido
NO* buscaEmProf(VERTICE *g, int i,int V, int* tam){
    NO* array = (NO*) malloc(sizeof(NO) * v);
        for (int i = 0; i < V; i++){
        if (g[i].inicio->flag == 0){
            g[i].inicio->flag = 1;
            array[i] = g[i].inicio;
            NO *p = g[i].inicio->prox;
            while (p){
                if (g[p->v].inicio->flag == 0)
                    buscaEmProf(g, p->v, V);
                p = p->prox
            }
            g[i].inicio->flag = 2;
            *tam++;
        }
    }
    return array;
}

NO* contaSubgrupos(VERTICE* g, int V, int* array){
    int tam;
    int resp = 0;
    NO* array = (NO*) malloc(sizeof(NO) * V);
    for(int i = 0; i < V; i++){
        tam = 0;
        if(g[i].flag == 0){
            array[resp] = buscaEmProf(g, i, V, &tam);
            
            resp++;
        }
    }
    
}

//pendente fazer