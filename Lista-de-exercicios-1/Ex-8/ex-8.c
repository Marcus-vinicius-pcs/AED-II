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

bool ehSubgrafo(VERTICE* g1, VERTICE* g2, int V1, int V2){
    for(int j = 0; j < V2; j++){
            NO* p1 = g2[j].inicio->prox;
            for(int i = 0; i < V1; i++){
                NO* p2 = g1[i].inicio->prox;
                if(g1[i].inicio->v == g2[j].inicio->v){
                    while(p1){
                        while(p2){
                            if(p1->v != p2->v)
                                return false;
                            printf("%i\n", p2->v);
                            p2 = p2->prox;
                        }
                        p1 = p1->prox;
                    }
                }
            }
        }
    return true;
}