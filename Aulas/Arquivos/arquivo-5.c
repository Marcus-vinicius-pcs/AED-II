//KEYSORT

typedef struct{
    char chave[20];
    int end;
} REG;

REG tabela[MAX];
int prox = 0;
int s = sizeof(REG);

//bool inserir(&tabela, registro, chave, end)
//int busca(&tabela, chave)
//int excluir(&tabela, chave)

REG r;
FILE* arq = fopen("dados.bin", "rb");
while(1 == fread(&r, s, 1, arq)){
    bool ok = inserir(&tabela, r, chave, prox);
    if(!ok) break;
    prox++;
}
fclose(arq);
/*
1 - Copiar a tarefa de chars e end
Em memória principal

2 - Percorre a tabela usando um contador

3 - Pata cada item da tabela troca registro eo endereço com registro do novo endereço (contador)
*/

int end = busca(tabela, r, chave);
if(end > -1)
//erro

fseek(arq, s*end, SEEK_SET);
fread(&r, s, 1, arq);

int end = excluirIndice(tabela, chave);
if(end == -1)
//ERRO

fseek(tabela, s*end, SEEK_SET);
rvazo.valido = 0;
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

