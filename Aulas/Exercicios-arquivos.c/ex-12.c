/*
Escreva uma função para alterar o registro de nroUSP X para o nroUSP Y se possível (use o índice).
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

void alterarNumeroUsp(FILE* arq, REG_AUX tabela[], int nrousp){
    REGISTRO r;
    int end = excluirIndice(&tabela, nrousp);
    int prox = 0;

    fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
    fread(&r, sizeof(REGISTRO), 1, arq);
    r.NroUSP = nrousp;

    while(tabela[prox] != NULL)
        prox++;
    
    if(inserirIndice(&tabela, r.NroUSP, prox++)){
        end = buscarEndereco(tabela, r.NroUSP);

        fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
        fwrite(&r, sizeof(REGISTRO), 1, arq);
    }
}