FILE* arq;

if(arq = Fopen("teste.txt", "r") == NULL)
//ERRO
else 
//use o arquivo

/*
* codificação: texto x binário

*unidade dos dados: bytes(char)
                    tipos básicos (numeros, strings, etc)
                    registros

*acesso: sequencial
*/

/*
r = leitura
w = escrita (cria novo)
a = anexar

acrescenta + para leitura+escrita
acescentar b para binário
*/

//Arquivos texto
fprintf(arq, "valor = %d", x); //escrita
fscanf(arq, "&d", &x); //leitura

fgets(palavra, MAX, arq); //ler frases (strings)

//Ler arquivo texto
1 - fopen
2 - while(feof(arq) == 0){

}
3 - Ler
4 - Fclose(arq);

FILE* arq;
arq = Fopen("exemplo txt", "r");
if(!arq){
    //FIM
}
while(Feof(arq) == 0){
    c = getc(arq);
    printf("%c", c);
}
fclose(arq);
