/*
Implemente o procedimento de ordenação KeySort, que dado um arquivo arq1 cria uma tabela
temporária de chaves em memória (idêntica a uma tabela de índices primários) e então reescreve o
arquivo em um novo arquivo de saída arq2, na ordem correta de chaves (exercício completo e
altamente recomendável).
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

bool inserirNaTabela(REGISTRO** tabela, int chave, int end){
    
}

void keySort(FILE* arq1){
    FILE* arq2 = fopen("arquivo_ordenado.bin", "wb");
    REGISTRO tabela[20];
    REGISTRO r;
    int prox = 0;

    while(1 == fread(&r, sizeof(REGISTRO), 1, arq1)){

    }
}

