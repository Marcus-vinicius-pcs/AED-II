/*
Serielização de grafos
*/

#include <stdio.h>
#define true 1;
#define false 0;
typedef int bool;

typedef struct adj{
    int valor;
    struct adj* prox;
} NO;

typedef struct {
    NO* inicio;
    int vertices;
} VERTICE;

//GRAFOS
void escrita(FILE* arq, VERTICE* g){
    fwrite(&g, sizeof(VERTICE), 1, arq);

    for(int i = 0; i < g->vertices; i++)
    {
        NO* p = g[i].inicio;
        while(p)
        {
            int origem = i;
            int valor = p->valor;
            int destino = p->prox->valor;

            fwrite(&origem, sizeof(int), 1, arq);
            fwrite(&valor, sizeof(int), 1, arq);
            fwrite(&destino, sizeof(int), 1, arq);

            p = p->prox;
        }
    }
}


void leitura(FILE* arq){
    int V;
    fread(&V, sizeof(int), 1, arq);
    VERTICE* g = (VERTICE*) malloc(sizeof(VERTICE) * V);
    inicializarGrafo(&g);

    int origem, valor, destino;

    while(1 == fread(&origem, sizeof(int), 1, arq))
    {
        fread(&valor, sizeof(int), 1, arq);
        fread(&destino, sizeof(int), 1, arq);
        insereAresta(g, origem, destino, valor);
    }

}
///////////////////////////////////////////////////////////////

//Listas Sequenciais
void escrita(FILE* arq, int* lista){
    int i = 0;
    while(lista[i])
    {
        fwrite(&lista[i], sizeof(int), 1, arq);
        i++;
    }
}

int* leitura(FILE* arq){
    int nroElem = 0;
    while(1 == fread(&nroElem, sizeof(int), 1, arq))
        nroElem++;

    int* lista;
    fread(lista, sizeof(int), nroElem, arq);
}