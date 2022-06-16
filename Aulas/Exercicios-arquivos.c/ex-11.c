/*
Escreva uma função para alterar o curso de um registro de nroUSP X para o curso Y (use o índice).
*/

#include <stdio.h>
#define true 1;
#define false 0;
typedef int bool;
#define MAX 20;


typedef struct {
int NroUSP; // chave primária
int curso;
int estado;
int idade;
bool valido; // para exclusão lógica
} REGISTRO;

typedef struct {
    int chave;
    int end;
} REG_AUX;

/*
bool inserirÍndice(REGISTRO Tabela[], int nroUSP, int end) //inserção em tabela ordenada, retornando true/false
int buscarEndereço(REGISTRO Tabela[], int nroUSP) // retorna -1 se end não existe
int excluirÍndice(REGISTRO Tabela[], int nroUSP) // retorna o endereço exluído, ou -1 se não encontrar
*/

void alterarCurso(FILE* arq, REG_AUX tabela[], int nrousp, int curso){
    REGISTRO r;
    int end = buscarEndereco(tabela, nrousp);

    fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
    fread(&r, sizeof(REGISTRO), 1, arq);
    r.curso = curso;

    fwrite(&r, sizeof(REGISTRO), 1, arq);
}