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


