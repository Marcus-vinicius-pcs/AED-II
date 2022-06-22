/*
Ordenação externa:

(1) Ler e Ordenar cada bloco individualmente
(2) Reescrever cada bloco ordenado em arquivos temporários (corridas = run)
(3) Ler porções de chaves de todas vias simultaneamente e selecionar a melhor
(4) Escrever a melhor chave em um arquivo de saída e repetir
*/

//inicialização
int pickChave[4];
int tamanhobuffer = 1;
int n = 4;
int i;
for(i = 0; i < n; i++){
    FILE* arq[i] = fopen(name[i], "rb");
    pickChave[i] = infinito;
    int lidos = fread(&pickChave[i], sizeof(int), tamanhoBuffer, arq[i]);
    if(lidos < tamanhobuffer)
        fclose(arq[i]));
}

//intercalação
int arqAlvo = -1;
int menorChave = -1;
while(true){
    for(int i = 0; i < n; i++){
        if(pickChave[i] < menorChave){
            arqAlvo = i;
            menorChave = pickChave[i];
        }
        if(arqAlvo == -1){
            fclose(saida);
        }
    }

    fwrite(&menorChave, sizeof(int), 1, saida);
    pickChave[i] = infinito;
    lidos = fread(&pickchave[i], sizeof(int), 1, arq[i]);
    if(lidos < tamanhobuffer)
        fclose(arq[i]);
}





