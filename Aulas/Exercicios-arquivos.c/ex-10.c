/*
Escreva uma função para excluir todos os registros do curso X (use o índice).
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

void excluirRegistrosDoCursoX(int curso, FILE* arq, REG_AUX tabela[]){
    REGISTRO r;
    int end;
    
    while(1 == fread(&r, sizeof(REGISTRO), 1, arq)){
        if(r.curso == curso){
            r.valido = false;
            end = excluirIndice(&tabela, r.NroUSP);

            fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
            fwrite(&r, sizeof(REGISTRO), 1, arq);
        }
    }
}