/*
- grafo em listas de adjacencias
- n vertices identificados com um campo char id[10]
- cada aresta possui int velocidade
- Escrever um algoritmo que armazena o conteudo completo do grafo em um arquivo
*/

#include <stdio.h>

typedef struct adj
{
    char id[10];
    int velocidade;
    struct adj* prox;
} NO;

typedef struct 
{
    NO* inicio;
    int vertices;
} VERTICE;

typedef struct 
{
    char id[10];
    char destino[10];
    char origem[10];
    int velocidade;
} REGISTRO;


void armazenaGrafo(VERTICE* g){
    FILE* arq = fopen("grafo.bin", "wb");
    REGISTRO r;

    for(int i = 0; i < g->vertices; i++)
    {
        NO* p = g[i].inicio;

        while (p)
        {
            r.id = p->id;
            r.destino = p->prox->id;
            r.origem = g[i].inicio->id;
            r.velocidade = p->velocidade;

            fwrite(&r, sizeof(REGISTRO), 1, arq);

            p = p->prox;
        }
        
    }

    fclose(arq);
}
