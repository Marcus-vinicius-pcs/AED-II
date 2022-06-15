/*
Faça uma cópia invertida de arq1 em um novo arquivo arq2, ou seja: copie o último registro (n) de
arq1 para o início de arq2, depois copie o registro n-1 para a segunda posição etc.
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

void copiaInvertida(FILE* arq1){
    FILE* arq2 = fopen("copia_invertida.bin", "wb");
    fseek(arq1, 0, SEEK_END);
    REGISTRO r;

    while(true){
        fseek(arq1, -sizeof(REGISTRO), SEEK_CUR);
        int lido = fread(&r, sizeof(REGISTRO), 1, arq1);

        if(lido != 1)
            break;

        fwrite(&r, sizeof(REGISTRO), 1, arq2);
    }
    fclose(arq2);
}