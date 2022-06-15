/*
Escreva uma função para alterar o curso de um aluno de nroUSP X para o curso Y.
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

void alterarCurso(FILE* arq, int curso, int nroUsp){
    REGISTRO r;

    while(1 == fread(&r, sizeof(REGISTRO), 1, arq)){
        if(r.NroUSP == nroUsp){

            fseek(arq, -sizeof(REGISTRO), SEEK_CUR);

            r.curso = curso;
            fwrite(&r, sizeof(REGISTRO), 1, arq);
        }
    }
}