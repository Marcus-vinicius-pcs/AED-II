/*
Escreva uma função para inserir um novo registro r no arquivo, tomando cuidado para evitar
chaves duplicadas (use o índice).
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

bool inserirRegistro(FILE* arq, REGISTRO reg, REG_AUX tabela[]){
    int end = buscarEndereço(tabela, reg.NroUSP);

    if(end != -1)
        return false;
    
    fseek(arq, 0, SEEK_END);
    fwrite(&reg, sizeof(REGISTRO), 1, arq);

    int prox = 0;
    while(tabela[prox] != NULL)
        prox++;

    inserirIndice(&tabela, reg.NroUSP, prox++);

    return true;
}