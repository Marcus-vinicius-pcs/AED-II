//1. Reescreva um arquivo arq1 em um novo arquivo arq2 eliminado os registros inválidos.
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

void removeInvalidos(FILE* arq1){
    FILE* arq2 = fopen("reg_validos.bin", "wb'");
    REGISTRO resp;

    fseek(arq1, 0, SEEK_SET);
    while(1 == fread(&resp, sizeof(REGISTRO)), 1, arq1){
       
        if(resp.valido)
            fwrite(&resp, sizeof(REGISTRO), 1, arq2);
    }
    fclose(arq2);
}
