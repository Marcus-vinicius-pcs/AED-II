#include <stdio.h>
#include <stdlib.h>

#define true 1;
#define false 0;
typedef int bool;

typedef struct adj {
    int v;
    int codigo;
    struct adj* prox;
} NO;

typedef struct {
    NO* inicio;
} VERTICE;

bool ehSubgrafo(int m[10][10], VERTICE* g){
    for(int i = 0; i < 10; i++){
        NO* p = g[i].inicio->prox;
        for(int j = 0; j < 10; j++){
            while(p){
                if((m[i][j] == 1) && (p->v != j))
                    return false;
                p = p->prox;
            }
        }
    }
    return true;
}

//pendente teste