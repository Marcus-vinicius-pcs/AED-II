/*
Escreva uma função para alterar o registro de nroUSP X para o nroUSP Y se possível (verifique quais
índices precisam ser atualizados).
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

void alterarNroUsp(FILE* arq, INDICE_PRIM* tabelaprim, INDICE_SEC_CURSO* tabelacurso, INDICE_SEC_ESTADO* tabelaest, int nrousp)
{
    int end = excluirIndice(&tabelaprim, nrousp);
    excluirIndice(&tabelacurso, nrousp);
    excluirIndice(&tabelaest, nrousp);
    fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
    REGISTRO r;
    fread(&r, sizeof(REGISTRO), 1, arq);
    r.NroUSP = nrousp;
    int prox = 0;
    while(tabelaprim[prox])
        prox++;
    
    inserirIndice(&tabelaprim, nrousp, prox++);

    prox = 0;
    while(tabelacurso[prox])
        prox++;
    inserirIndice(&tabelacurso, nrousp, prox++);

    prox = 0;
    while(tabelaest[prox])
        prox++;
    inserirIndice(&tabelaest, nrousp, prox++);
}