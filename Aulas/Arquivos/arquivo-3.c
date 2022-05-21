#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int idade;
    int chave;
} TIPO_REG;

//transferencia
fwrite(ponteiro, sizeof(TIPO_REG), quant_Maxima, arq);
fread(ponteiro, sizeof(TIPO_REG), quant_Maxima, arq);

TIPO_REG dados[MAX];
int prox = 0;
FILE* arq = fopen("dados.bin", "rb");
if(arq){
    prox = fread(dados, sizeof(TIPO_REG), MAX, arq);
    fclose(arq);
}

//entrar mais dados

arq = fopen("dados.bin", "wb");
fwrite(dados, sizeof(TIPO_REG), prox, arq);
fclose(arq);

TIPO_REG* buscaSeq(FILE* arq, int chave){
    rewind(arq); //voltar ao byte 0
    TIPO_REG resp;
    strcpy(resp.name, "");
    resp.idade = 0;
    resp.chave = -1; //não existe
    while(1 == fread(&resp,sizeof(TIPO_REG), 1, arq)){
        if(resp.chave == chave)
            return (&resp);
    }
    resp.chave = 1;//não achou
    return (&resp);
}

fseek(arq, deslocamento, referencia); // Referencia: SEEK_SET, SEEK_CUR, SEEK_END

TIPO_REG* buscaSeq(FILE* arq, int n){
    rewind(arq); //voltar ao byte 0
    TIPO_REG resp;
    strcpy(resp.name, "");
    resp.idade = 0;
    resp.chave = -1; //não existe
    fseek(arq, n * sizeof(TIPO_REG), SEEK_SET);
    int lido = fread(&resp, sizeof(TIPO_REG), 1, arq);
}

void aniversario(FILE* arq, int n){
    rewind(arq); //voltar ao byte 0
    TIPO_REG resp;
    strcpy(resp.name, "");
    resp.idade = 0;
    resp.chave = -1; //não existe
    fseek(arq, n * sizeof(TIPO_REG), SEEK_SET);
    int lido = fread(&resp, sizeof(TIPO_REG), 1, arq);
    if(lido == 1){
        resp.idade++;
        fseek(arq, -sizeof(TIPO_REG), SEEK_CUR);
        fwrite(&resp, sizeof(TIPO_REG), 1, arq);
    }
}

/*
Ex:
Dado um arquivo com registros logicamente excluidos,
reesecrever o arquivo efetuando a exclusão física
*/
void limparArquivo(char nome1[20], char nome2[20]){
    FILE* arq1 = fopen(nome1, "rb");
    FILE* arq2 = fopen(nome2, "wb");
    TIPO_REG x;
    while(1 == fread(&x, sizeof(TIPO_REG), 1, arq1)){
        if(x.valido == 1){
            fwrite(&x, sizeof(TIPO_REG), 1, arq2);
        }
        fclose(arq1);
        fclose(arq2);
    }
}

/*
Ex (1) Excluir logicamente um registro de chave ch
Ex (2) Converter um arquivo de registros de tamanho fixo para arquivo texto com delimitadores;
Ex (3) Ou vice-versa
Ex (4) Comparar 2 arquivos de tamanho fixo retornando true/false
Ex (5) Idem, porém considerando um arquivo com registros de tamanho fixo e o outro variável
Ex (6) O mesmo que o 4 porém considerando que a ordem pode ser diferente
*/