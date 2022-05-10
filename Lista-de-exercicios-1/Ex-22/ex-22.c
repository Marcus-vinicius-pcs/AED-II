#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;
typedef int bool;

typedef struct adj {
    int v;
    int flag;
    int ocupacao;
    struct adj* prox;
} NO;

typedef struct {
    NO* inicio;
} VERTICE;


//Busca em largura que retorna o caminho mais curto
NO* buscaSalaVazia(VERTICE* g, int i){
    FILA f;
    inicializarFIla(&f);
    zerarFlags(g);
    zerarVia(g);
    g[i].flag = 1;
    entrarFila(&f, i); 
    while(f.inicio){ 
        i = sairFila(&f); 
        p = g[i].inicio; 
        while(p){
            if(g[p->v].flag == 0){
                g[p->v].flag = 1; 
                entrarFila(&f, p->v); 
                g[p->v].via = i;
                if(g[p->v].ocupacao == 0){
                    sairFila(&f);
                    return g[p->v];
                }
            }
            p = p->prox;
        }
    }
    return NULL;
}
//pendente teste


