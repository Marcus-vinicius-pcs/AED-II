/*
Escreva uma função para inserir um novo registro r no arquivo, tomando cuidado para evitar
chaves duplicadas (verifique quais índices precisam ser atualizados).
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

/*
bool inserirÍndice(REGISTRO Tabela[], int nroUSP, int end) //inserção em tabela ordenada, retornando true/false
int buscarEndereço(REGISTRO Tabela[], int nroUSP) // retorna -1 se end não existe
int excluirÍndice(REGISTRO Tabela[], int nroUSP) // retorna o endereço exluído, ou -1 se não encontrar
*/

//NO* chavesCurso(int curso)
//NO *chavesEstado(int estado)

bool inserirRegistro(REGISTRO reg, FILE* arq, INDICE_PRIM tabelaprim[], 
INDICE_SEC_CURSO tabelacur[], INDICE_SEC_ESTADO tabelaest[])
{

    int prox=  0;

    while (tabelaprim[prox] != NULL)
    {
        prox++;
    }
    
    if(!inserirIndice(&tabelaprim, reg.NroUSP, prox++) || 
       !inserirIndiceSecCurso(&tabelacur, reg.curso, prox++) ||
       !inserirIndiceSecEstado(&tabelaest, reg.estado, prox++))
    {
        return false;
    }

    
    fwrite(&reg, prox*sizeof(REGISTRO), 1, arq);

    return true;
}