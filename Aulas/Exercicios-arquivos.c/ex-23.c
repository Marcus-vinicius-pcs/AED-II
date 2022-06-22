/*
limpar os registros inválidos de um arquivo
*/

#include <stdio.h>
#define true 1;
#define false 0;
typedef int bool;

typedef struct 
{
    bool valido;
} REGISTRO;

void limpaArquivo(FILE* arq)
{
    REGISTRO r;
    FILE* newArq = fopen("Novos_dados.bin", "wb");


    fseek(arq, 0, SEEK_SET);
    while(1 == fread(&r, sizeof(REGISTRO), 1, arq))
    {
        if(r.valido)
            fwrite(&r, sizeof(REGISTRO), 1, newArq);
        
    }

    fclose(newArq);
}