#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// ######### ESCREVA O NRO DO SEU GRUPO AQUI CONFORME JA CADASTRADO EM
// https://docs.google.com/spreadsheets/d/1_wy0Uko3vX8GE07G1WP4X6X6-yRdu6eCpLdmmRvU7EM/edit?usp=sharing
// NOVAS DUPLAS NAO SAO ACEITAS

int grupo()
{
  return 0;
}

// ######### ESCREVA O NROUSP AQUI
int nroUSP1()
{
  return 12543478;
}

int nroUSP2()
{
  return 0;
}

//-------------------------------------------

// CHLINK eh um par <chave,link> - dentro de cada página há 3 CHLINKs
typedef struct
{
  int chave;
  int linkdir;
} CHLINK;

// definicao de pagina da árvore / registro do arquivo
typedef struct
{
  int np;         // armazene aqui o nro da pagina no arquivo
  int cont;       // armazene aqui a quantidade de chaves existentes no vetor CHLINK[]
  CHLINK item[3]; // a chave[0] eh desprezada, e o linkdir[0] eh na verdade o link esquerdo da chave[1]
} PAGINA;

// funcao principal
void excluir(char nomearq[], int *raiz, int ch);

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------

bool excluirChave(int ch, FILE* arq)
{
  int pos = -1;
  PAGINA* p = carregarPaginaChave(arq, ch);
  if (p == NULL)
    return false;
  for(int i = 1; i <= p->cont; i++)
  {
    if(p->item[i].chave == ch)
      pos = i;
  }

  if(pos == -1)
    return false;

  p->item[pos].chave = p->item[pos+1].chave;
  p->item[pos].linkdir = p->item[pos+1].linkdir;
  p->cont--;
  return true;
}

void excluiChave(FILE* arq, int ch);

void excluir(char nomearq[], int *raiz, int ch)
{
  if(*raiz == -1)
    return;
  
  PAGINA* p;
  PAGINA* pai;
  PAGINA* irma;
  int* indexOrigem;
  FILE* arq = fopen(nomearq, "wb+");
  p = carregarPaginaChave(arq, ch, &pai, &indexOrigem, *raiz); //carrega uma pagina e armazenna o pai dela buscando pela chave

  //Tratando o caso 1 (exclusão sem underflow)
  if(p->cont == 2)
    excluiChave(arq, ch);

  //Tratando o caso 2 (exclusão na raiz)
  if(p->np == *raiz)
    sobeSucessor(ch, arq);
  
  //tratando o caso 3 (exclusão com redistribuição possível)
  if(pai->item[*indexOrigem+1].linkdir)

  // abra o arquivo
  // faca a exclusao
  // atualize o nro da *raiz se necessario
  // feche o arquivo
}


PAGINA *carregarPagina(FILE *arq, int nroPag)
{
  PAGINA *r;
  rewind(arq);
  while (1 == fread(r, sizeof(PAGINA), 1, arq))
  {
    if (r->np == nroPag)
      return r;
  }
  return NULL;
}

PAGINA *carregarPaginaChave(FILE *arq, int chave, PAGINA** pai, int** indexOrigem, int raiz)
{
  PAGINA *p;
  PAGINA* raiz;
  
  raiz = carregaPagina(arq, raiz);
  p = raiz;
  for(int i = p->cont; i >= 1; i--)
  {
    if(p->item[i].chave == chave)
      return p;

    else if (p->item[i].chave < chave)
      *pai = p;
      *indexOrigem = i;
      p = carregarPagina(arq, p->item[i].linkdir);
  }

  return NULL;
}

int sobeSucessor(int ch, FILE* arq)
{
  int pos = -1;
  PAGINA* p = carregarPaginaChave(arq, ch);
  PAGINA* aux;
  int j;

  if(p == NULL)
    return -1;
  for(int i = 1; i <= p->cont; i++)
  {
    if(p->item[i].chave == ch)
      pos = i;
  }
  if(pos == -1)
    return -1;

  aux = carregarPagina(arq, p->item[pos].linkdir);
  while(aux->item[0].linkdir > -1)
  {
    aux = carregarPagina(arq, aux->item[0].linkdir);
  }
  return aux->item[1].chave;
}

int main()
{

  PAGINA p1;
  p1.np = 0;
  p1.cont = 1;
  CHLINK c1;
  c1.chave = 0;
  c1.linkdir = 1;
  CHLINK c2;
  c2.chave = 13;
  c2.linkdir = 2;
  p1.item[0] = c1;
  p1.item[1] = c2;
  CHLINK c27;
  c27.chave = -1;
  c27.linkdir = -1;
  p1.item[2] = c27;

  PAGINA p2;
  p2.np = 1;
  p2.cont = 2;
  CHLINK c3;
  c3.chave = 0;
  c3.linkdir = 3;
  CHLINK c4;
  c4.chave = 4;
  c4.linkdir = 4;
  CHLINK c5;
  c5.chave = 8;
  c5.linkdir = 5;
  p2.item[0] = c3;
  p2.item[1] = c4;
  p2.item[2] = c5;

  PAGINA p3;
  p3.np = 2;
  p3.cont = 2;
  CHLINK c6;
  c6.chave = 0;
  c6.linkdir = 6;
  CHLINK c7;
  c7.chave = 17;
  c7.linkdir = 7;
  CHLINK c8;
  c8.chave = 21;
  c8.linkdir = 8;
  p3.item[0] = c6;
  p3.item[1] = c7;
  p3.item[2] = c8;

  PAGINA p4;
  p4.np = 3;
  p4.cont = 2;
  CHLINK c9;
  c9.chave = 0;
  c9.linkdir = -1;
  CHLINK c10;
  c10.chave = 1;
  c10.linkdir = -1;
  CHLINK c11;
  c11.chave = 3;
  c11.linkdir = -1;
  p4.item[0] = c9;
  p4.item[1] = c10;
  p4.item[2] = c11;

  PAGINA p5;
  p5.np = 4;
  p5.cont = 2;
  CHLINK c12;
  c12.chave = 0;
  c12.linkdir = -1;
  CHLINK c13;
  c13.chave = 5;
  c13.linkdir = -1;
  CHLINK c14;
  c14.chave = 6;
  c14.linkdir = -1;
  p5.item[0] = c12;
  p5.item[1] = c13;
  p5.item[2] = c14;

  PAGINA p6;
  p6.np = 5;
  p6.cont = 2;
  CHLINK c15;
  c15.chave = 0;
  c15.linkdir = -1;
  CHLINK c16;
  c16.chave = 9;
  c16.linkdir = -1;
  CHLINK c17;
  c17.chave = 10;
  c17.linkdir = -1;
  p6.item[0] = c15;
  p6.item[1] = c16;
  p6.item[2] = c17;

  PAGINA p7;
  p7.np = 6;
  p7.cont = 2;
  CHLINK c18;
  c18.chave = 0;
  c18.linkdir = -1;
  CHLINK c19;
  c19.chave = 15;
  c19.linkdir = -1;
  CHLINK c20;
  c20.chave = 26;
  c20.linkdir = -1;
  p7.item[0] = c18;
  p7.item[1] = c19;
  p7.item[2] = c20;

  PAGINA p8;
  p8.np = 7;
  p8.cont = 2;
  CHLINK c21;
  c21.chave = 0;
  c21.linkdir = -1;
  CHLINK c22;
  c22.chave = 18;
  c22.linkdir = -1;
  CHLINK c23;
  c23.chave = 19;
  c23.linkdir = -1;
  p8.item[0] = c21;
  p8.item[1] = c22;
  p8.item[2] = c23;

  PAGINA p9;
  p9.np = 8;
  p9.cont = 2;
  CHLINK c24;
  c24.chave = 0;
  c24.linkdir = -1;
  CHLINK c25;
  c25.chave = 23;
  c25.linkdir = -1;
  CHLINK c26;
  c26.chave = 26;
  c26.linkdir = -1;
  p9.item[0] = c24;
  p9.item[1] = c25;
  p9.item[2] = c26;

  FILE *arq = fopen("arvore-b.bin", "wb+");
  fwrite(&p1, sizeof(PAGINA), 1, arq);
  fwrite(&p2, sizeof(PAGINA), 1, arq);
  fwrite(&p3, sizeof(PAGINA), 1, arq);
  fwrite(&p4, sizeof(PAGINA), 1, arq);
  fwrite(&p5, sizeof(PAGINA), 1, arq);
  fwrite(&p6, sizeof(PAGINA), 1, arq);
  fwrite(&p7, sizeof(PAGINA), 1, arq);
  fwrite(&p8, sizeof(PAGINA), 1, arq);
  fwrite(&p9, sizeof(PAGINA), 1, arq);
  PAGINA p;
  rewind(arq);

  while (1 == fread(&p, sizeof(PAGINA), 1, arq))
  {
    printf("Página: %i\n\n", p.np);

    for (int i = 0; i < 3; i++)
    {
      if (p.item[i].chave != -1)
        printf("Chave: %i Link da chave %i\n", p.item[i].chave, p.item[i].linkdir);
    }
    printf("Links:\n");
    for (int j = 0; j < 3; j++)
    {
      if (p.item[j].linkdir)
        printf(" %i ", p.item[j].linkdir);
    }
    printf("\n\n");
  }

  printf("TESTE CARREGA PAGINA\n\n");
  for (int i = 0; i < 9; i++)
  {
    PAGINA *teste = carregarPagina(arq, i);
    printf("%i ", teste->item[1].chave);
  }

  printf("\n\nNOVO TESTEEE\n\n");
  for (int i = 0; i < 27; i++)
  {
    PAGINA *teste1 = carregarPaginaChave(arq, i);
    if (teste1 != NULL)
      printf("%i página: %i\n", i, teste1->np);
  }

  printf("\n\nteste de encontrar o sucessor\n\n");
  printf("%i", encontrarSucessor(21, arq));

  
  fclose(arq);

  
}