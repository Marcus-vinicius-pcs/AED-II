#include <stdio.h>

#define FOPEN_MAX 20;

typedef struct{
    char* ptr;
    int cnt;
    char* base;
    int flag;
    int file;
    int charbuf;
    int bufsiz;
    char* tmpfname;
} FILE;

//Abertura do arquivo
/*
FILE* fd = fopen(<filename>, <flags>);

flags:
    r : apenas leitura (o arquivo precisa existir)
    w : cria arquivo vazio para escrita (apaga um arquivo já existente)
    a : adiciona conteúdo a um arquivo
    r+ : abre arquivo para leitura e escrita
    w+ : cria arquivo vazio para leitura e escrita
    a+ : abre arquivo para leitura e adição de dados
    b : inserir após as ags anteriores para trabalhar com arquivo binário, caso contrário será
    aberto em modo texto. (rb, wb, ...).
*/

//Fechamento do Arquivo
/*
fclose(<fd>);

fd : file descriptor, do tipo ponteiro FILE
*/

/*
Grupos de funções para manipulação de arquivos:
    ● por caractere
    ● por cadeia de caracteres
    ● dados formatados
    ● blocos de bytes
*/

//Por caractere
/*
fputc(<char>,<FILE>) : escreve um caractere no arquivo,
● <char> = fgetc(<FILE>) : lê um caractere do arquivo.
*/

//Por cadeia de caracteres
/*
● fputs(<char *>,<FILE>) : escreve uma string no arquivo,
● fgets(<char *>,<int>,<FILE>) : lê do arquivo uma determinada
  quantidade de caracteres e armazena a cadeia de caracteres numa variável,
  retorna NULL se fim de arquivo.
*/

//Por dados formatados
/*
● fprintf(<FILE>,”formatacao”, ...) : similar ao printf, escreve num arquivo a
  string formatada.
● fscanf(<FILE>,”formatacao”, ...) : similar ao scanf , arquivo strings
  formatadas, retorna EOF se fim de arquivo.
*/

//Por blocos de bytes (arquivos binários)
/*
● <size_read> = fread(<buffer>, <size_un>, <size_buffer>,
<FILE>) :
        ○ size_read : unidades lidas (0 se m de arquivo),
        ○ buffer : variavel que vai armazenar a leitura,
        ○ size_un : tamanho de cada unidade (bloco) de bytes a ser lido,
        ○ size_buffer : número de blocos
        ○ FILE : ponteiro FILE

● fwrite(<buffer>, <size_un>, <size_read>, <FILE>) : similar ao scanf , lê do
  arquivo strings formatadas, retorna EOF se fim de arquivo.
  
● fseek(<FILE>, <move_bytes>, <start_byte>) : move o ponteiro do arquivo
  para uma posição determinada.
*/