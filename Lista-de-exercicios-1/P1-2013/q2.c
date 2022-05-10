#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;
typedef int bool;

typedef struct adj {
    int v;
    int codigo;
    int flag;
    int via;
    struct adj* prox;
} NO;

typedef struct {
    NO* inicio;
} VERTICE;

typedef struct {
    NO* inicio;
    NO* final;
} FILA;

void inicializarFila(FILA* f){
    f->inicio = NULL;
    f->final = NULL;
}

void entrarFila(FILA* f, int i){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->v = i;
    novo->prox = NULL;
    if(f->inicio == NULL) f->inicio = novo;
    else f->final->prox = novo;
    f->final = novo;
}

int sairFila(FILA* f){
    if(f->inicio == NULL) return -1;
    int resp = f->inicio->v;
    NO* apagar = f->inicio;
    f->inicio = f->inicio->prox;
    free(apagar);
    if(f->inicio == NULL) f->final = NULL;
    return resp;
}

int buscaLarguraAdaptada(VERTICE* g, int i, int t){
    FILA f;
    inicializarFila(&f);
    g[i].inicio->flag = 1;
    entrarFila(&f, i); 
    while(f.inicio){ 
      //imprimirFila(&f);  
      i = sairFila(&f); 
        NO* p = g[i].inicio; 
        while(p){
           if(g[p->v].inicio->flag == 0){
                if(g[p->v].inicio->codigo == t){
                    return p->v;
                    while(f.inicio)
                        sairFila(&f);
                }
                else{
                    g[p->v].inicio->flag = 1; 
                    entrarFila(&f, p->v); 
                    g[p->v].inicio->via = i;
                }
            }
            p = p->prox;
        }
    }
  return -1;
}

int postoMaisProximo(VERTICE* g, int local){
    int posto = buscaLargura(g, local, 3); //3 simboliza o tipo do posto de gasolina
    return posto;
} 

//pendente teste