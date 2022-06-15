/*
Escreva uma função para inserir um novo registro r no arquivo, tomando cuidado para evitar
chaves duplicadas.
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

bool inserirRegistro(FILE* arq, REGISTRO newReg){
    REGISTRO r;

    while(1 == fread(&r, sizeof(REGISTRO), 1, arq)){
        if(r.NroUSP == newReg.NroUSP)
            return false;
    }

    fseek(arq, 0, SEEK_END);
    fwrite(&newReg, sizeof(REGISTRO), 1, arq);
    return true;
}