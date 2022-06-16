//KEYSORT
#include <stdio.h>
#include <stdlib.h>
#define MAX 20;

typedef struct{
    char chave[20];
    int end;
} REG_AUX;

REG_AUX tabela[MAX];
int prox = 0;

//bool inserir(&tabela, chave, end)
//int busca(&tabela, chave)
//int excluir(&tabela, chave)

void preencherTabela(REG_AUX* tabela[]){
    REG_AUX r;
    FILE* arq = fopen("dados.bin", "rb");
    while(1 == fread(&r, sizeof(REG_AUX), 1, arq)){
        if(!inserir(&tabela, r->chave, prox);) 
            break;
        prox++;
    }
    fclose(arq);
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

void ordenarArquivo(FILE* arq){
    FILE* arq2 = fopen("Arquivo_ordenado.bin", "wb");
    REG_AUX r;
    REG_AUX tabela;
    preencherTabela(&tabela);
    ordenarTabela(&tabela);

    while(1 == fread(&r, sizeof(REG_AUX), 1, arq)){
        int end = busca(tabela, r->chave);
        
        fseek(arq, end*sizeof(REG_AUX), SEEK_SET);
        fread(&r, sizeof(REG_AUX), 1, arq);
        fwrite(&r, sizeof(REG_AUX), 1, arq2);
    }

    fclose(arq2);
}


int end = busca(tabela, r->chave);
if(end > -1)
//erro

fseek(arq, s*end, SEEK_SET);
fread(&r, s, 1, arq);

int end = excluirIndice(tabela, chave);
if(end == -1)
//ERRO

fseek(tabela, s*end, SEEK_SET);
rvazio.valido = 0;
fwrite(&rvazio, s, 1, arq);

int end = buscaindice(tabela, chave);
if(end == -1);
//erro
fseek(arq, end*s, SEEK_SET);
fread(&r, s, 1, arq);
<alterar r>
fseek(arq, end*s, SEEK_SET);
fwrite(&r, s, 1, arq);


int end = excluirindice(tabela, chave);
if(end == -1)
//erro
fseek(arq, end*s, SEEK_SET);
fread(&r, s, 1, arq);
r.chave = nova chave;
fseek(arq, end*s, SEEK_SET)
fwrite(&r, s, 1, arq)
inserirIndice(tabela, nova chave);

