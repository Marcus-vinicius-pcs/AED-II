/*
Inserir os registros de B em A e atualizar a tabela de índices de A

bool inserirIndice(tabela, id, end);
int buscarindice(tabela, id);
int excluirindice(tabela, id);
*/

#include <stdio.h>

typedef struct 
{
    int cpf;
} REGISTRO;

typedef struct 
{
    int chave;
    int end;
} REG_AUX;



void inserirRegistros(FILE* arqA, FILE* arqB, REG_AUX* tabela)
{
    REGISTRO r;
    fseek(arqA, 0, SEEK_END);
    fread(&r, sizeof(REGISTRO), 1, arqA);
    int end = buscarindice(tabela, r.cpf) + 1;

    fseek(arqB, 0, SEEK_SET);
    while(1 == fread(&r, sizeof(REGISTRO), 1, arqB))
    {
        if(!inserirIndice(r.cpf, end))
            break;

        fwrite(&r, end*sizeof(REGISTRO), 1, arqA);
        end++;
    }
}