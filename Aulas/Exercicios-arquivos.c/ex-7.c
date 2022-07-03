/*
Implemente o procedimento de ordenação KeySort, que dado um arquivo arq1 cria uma tabela
temporária de chaves em memória (idêntica a uma tabela de índices primários) e então reescreve o
arquivo em um novo arquivo de saída arq2, na ordem correta de chaves (exercício completo e
altamente recomendável).
*/

#include <stdio.h>
#define true 1;
#define false 0;
#define MAX 20;

typedef int bool;

typedef struct {
    int NroUSP; // chave primária
    int curso;
    int estado;
    int idade;
    bool valido; // para exclusão lógica
} REGISTRO;

typedef struct{
    int chave;
    int end;
} REG_AUX;

//bool inserir(&tabela, chave, end)
//int busca(&tabela, chave)
//int excluir(&tabela, chave)

REG_AUX* preencherTabela(){
    REG_AUX tabela[MAX];
    int prox = 0;
    REG_AUX r;
    FILE* arq = fopen("dados.bin", "rb");

    while(1 == fread(&r, sizeof(REG_AUX), 1, arq)){

        if(!inserir(&tabela, r->chave, prox)) 
            break;
        prox++;
    }

    fclose(arq);
    return tabela;
}
/*
1 - Copiar a tabela de chars e end
Em memória principal

2 - Percorre a tabela usando um contador

3 - Para cada item da tabela troca registro e o endereço com registro do novo endereço (contador)
*/

void ordenaTabela(REG_AUX* tabela[]){

    int menorValor = 0;
    REG_AUX aux = NULL;
    for(int i = 0; i < MAX; i++){
        menorValor = i;
        for(int j = 0; j < MAX; j++){
            if(tabela[j].chave < tabela[menorValor].chave)
                menorValor = j;
        }
        aux = tabela[menorValor];
        tabela[menorValor] = tabela[i];
        tabela[i] = aux;
    }
    free(aux);
}

void keySort(FILE* arq1){
    FILE* arq2 = fopen("Arquivo_ordenado.bin", "wb");
    REG_AUX r;
    REG_AUX* tabela;
    preencherTabela(&tabela);
    ordenarTabela(&tabela);

    fseek(arq2, 0, SEEK_SET);
    for(int i = 0; i < MAX; i++)
    {
        fread(&r, tabela[i].end*sizeof(REGISTRO), 1, arq1);
        fwrite(&r, sizeof(REGISTRO), 1, arq2);
    }

    fclose(arq2);
}

//refazer