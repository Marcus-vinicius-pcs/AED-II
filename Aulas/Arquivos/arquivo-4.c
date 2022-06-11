#include <stdio.h>

typedef struct {
    int nrousp;
    int salario;
    char name[20];
    int valido;
} REG;

//(1) Busca sequencial retornando "endereço" do registro

int buscaSeqEndereco(FILE* arq, int ch, REG* r){
    int end = 0;
    while(1 == fread(r, sizeof(REG), 1, arq)){
        if(r->nrousp == ch) return end;
        else end++;
    }
    return (-1) //Não existente
}

//(2) Taxa de registros com chaves de posição

void tvocon(FILE* arq, int ch1, int ch2){
    REG r1, r2;
    int end = buscaSeqEndereco(arq, ch1, &r1);
    int end2 = buscaSeqEndereco(arq, ch2, &r2);
    fseek(arq, end1*sizeof(REG), SEEK_SET);
    fwrite(&r2, sizeof(REG), 1, arq);
    fseek(arq, end2*sizeof(REG), SEEK_SET);
    fwrite(&r1, sizeof(REG), 1, arq);
}

//(3) CRIAR UMA CÓPIA INVERTIDAD DE UM ARQUIVO
void inverter(FILE* arq1){
    FILE* saida = fopen("inversao.bin", "wb");
    fseek(arq1, 0, SEEK_END);
    while(true){
        fseek(arq1, -sizeof(REG), SEEK_CUR);
        int lido = fread(&r, sizeof(REG), arq1);
        if(lido == 1) break;
        fwrite(&r, sizeof(REG), saida);
    }
    fclose(saida);
}

//(4) Excluir todas as ocorrencias de uma dada chave em arquivo com chaves repetidas
void excluirOcorrencias(FILE* arq, int ch){
    REG* r;
    while(1 == fread(&r, sizeof(REG), 1, arq)){
        if(r->nrousp == ch && r->valido == 1){
            r->valido = 0;
            fseek(arq, -sizeof(REG), SEEK_CUR);
        }
        fwrite(&r, sizeof(REG), 1, arq);
    }
}

//5) Anexar um arquivo arq2, ao final de um arquivo arq2
void anexar(FILE* arq1, FILE* arq2){
    REG r;
    fseek(arq1, 0, SEEK_END);
    while(1 == fread(&r, sizeof(REG), 1, arq2)){
        fwrite(&r, sizeof(REG), 1, arq1);
    }
}

//(6) Acrescentar em arq1 os registros de arq2 mas sem repetição
void acrescentarSemRepeticao(FILE* arq1, FILE* arq2){
    REG r;
    fseek(arq1, 0, SEEK_END);
    while(1 == fread(&r, sizeof(REG), 1, arq2)){
        REG aux;
        int end = buscaSeqEndereco(arq1, r.nrousp, &aux);
        fseek(arq1, 0, SEEK_END);
        if(end != -1) continue;
        fwrite(&r, sizeof(REG), 1, arq1);
    }
}