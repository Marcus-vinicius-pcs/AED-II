/*
Escreva uma função para excluir todos os registros do curso X
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

void excluirRegistros(FILE* arq, int curso){
    REGISTRO r;

    while(1 == fread(&r, sizeof(REGISTRO), 1, arq)){
        if(r.curso == curso)
            r.valido == 0;
    }
}