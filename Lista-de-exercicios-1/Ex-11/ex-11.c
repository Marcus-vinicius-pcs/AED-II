/*
Considere um grafo dirigido em lista de adjacências representando uma rede de chamadas
telefônicas entre diversas unidades de uma empresa, onde cada vértice representa uma unidade, e
cada aresta representa uma chamada efetuada. As unidades podem estar em diferentes países,
identificados por um campo int país definido no respectivo vértice. Problema: a conta de telefone
global da empresa está muito alta. Escreva um algoritmo que identifique a unidade que efetua
chamadas para o maior número de países. Havendo empate, retorne qualquer resposta possível.

*/

#include <stdio.h>
#include <stdlib.h>


#define true 1;
#define false 0;

typedef int bool;

typedef struct adj {
    int v;
    int flag;
    int pond;
    int pais;
    struct adj* prox;
} NO;

typedef struct {
    NO* inicio;
} VERTICE;

int Max(int array[], int tam){
    int resp = 0;
    for(int i = 0; i < tam; i++){
        if(array[i] > array[resp])
            resp = i;
    }
    return resp;
}

int identificaMaiorLigacao(VERTICE* g, int V){
    int* contArray = (int*) malloc(sizeof(int) * V);
    int cont;
    for(int i = 0; i < V; i++){
        NO* p = g[i].inicio->prox;
        cont = 0;
        while(p){
            cont++;
            p = p->prox;
        }
        contArray[i] = cont;
    }
    int index = Max(contArray, V);
    return g[index].inicio->pais;
}