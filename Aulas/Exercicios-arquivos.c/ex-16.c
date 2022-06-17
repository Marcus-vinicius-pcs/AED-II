/*
Escreva uma função para excluir todos os registros do curso X (verifique quais índices precisam ser
atualizados).
*/

#include <stdio.h>
#define true 1;
#define false 0;
typedef int bool;

#define MAX 20;



typedef struct {
    int chave;
    int end;
} INDICE_PRIM;

typedef struct {
    int chave_primaria;
    int curso;
} INDICE_SEC_CURSO;

typedef struct {
    int chave_primaria;
    int estado;
} INDICE_SEC_ESTADO;

typedef struct {
int NroUSP; // chave primária
int curso;
int estado;
int idade;
bool valido; // para exclusão lógica
} REGISTRO;

typedef struct adj
{
    int chave;
    struct adj* prox;
} NO;

/*
bool inserirÍndice(REGISTRO Tabela[], int nroUSP, int end) //inserção em tabela ordenada, retornando true/false
int buscarEndereço(REGISTRO Tabela[], int nroUSP) // retorna -1 se end não existe
int excluirÍndice(REGISTRO Tabela[], int nroUSP) // retorna o endereço exluído, ou -1 se não encontrar
*/

//NO* chavesCurso(int curso)
//NO* chavesEstado(int estado)

void excluirRegistros(FILE* arq, int nrousp, INDICE_PRIM* tabela){
    REGISTRO r;
    int end = 0;

    while(end != -1)
    {
        end = excluirIndice(&tabela, nrousp);

        fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
        fread(&r, sizeof(REGISTRO), 1, arq);
        r.valido = false;
        fwrite(&r, sizeof(REGISTRO), 1, arq);
    }
}