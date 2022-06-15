/*
Escreva uma função que, dada um nroUSP X, retorne o registro correspondente.
*/

#include <stdio.h>
#define true 1;
#define false 0;

typedef int bool;

typedef struct {
    int NroUSP; // chave primária
    int curso;
    int estado;
    int idade;
    bool valido; // para exclusão lógica
} REGISTRO;

REGISTRO* retornaRegistro(FILE* arq, int nroUsp){
    REGISTRO r;
    
    while(fread(&r, sizeof(REGISTRO), 1, arq) == 1){
        if(r.valido && r.NroUSP == nroUsp)
            return &r;
    }
}