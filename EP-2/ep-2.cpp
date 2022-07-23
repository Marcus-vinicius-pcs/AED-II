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
  return 12692197;
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

PAGINA *carregarPagina(FILE *arq, int nroPag)
{
  PAGINA *r = (PAGINA *)malloc(sizeof(PAGINA));
  rewind(arq);
  fseek(arq, nroPag * sizeof(PAGINA), SEEK_SET);

  if (1 == fread(r, sizeof(PAGINA), 1, arq))
    return r;
  else
    return NULL;
}

void imprimirArvore(FILE *arq, int raiz)
{
  PAGINA *p = (PAGINA *)malloc(sizeof(PAGINA));
  rewind(arq);
  while (1 == fread(p, sizeof(PAGINA), 1, arq))
  {
    if (p->cont > 0)
    {
      printf("Página: %i\n\n", p->np);

      for (int i = 0; i <= p->cont; i++)
      {
        if (p->item[i].chave != -1)
          printf("Chave: %i Link da chave %i\n", p->item[i].chave, p->item[i].linkdir);
      }
      printf("Links:\n");
      for (int j = 0; j <= p->cont; j++)
      {
        if (p->item[j].linkdir)
          printf(" %i ", p->item[j].linkdir);
      }
      printf("\n\n");
    }
  }
}

PAGINA *carregarPaginaChave(FILE *arq, int chave, int *pos, int raiz)
{
  rewind(arq);
  PAGINA *p = carregarPagina(arq, raiz);

  int i = p->cont;
  while (i >= 0 && p != NULL)
  {
    if (p->item[i].chave == chave)
    {
      *pos = i;
      return p;
    }
    else if (chave > p->item[i].chave)
    {
      p = carregarPagina(arq, p->item[i].linkdir);
      i = p->cont;
    }
    else
    {
      i--;
    }
  }

  return NULL;
}

bool removeChave(FILE *arq, int ch, int raiz)
{
  rewind(arq);
  int pos = -1;
  PAGINA *p = carregarPaginaChave(arq, ch, &pos, raiz);

  if (p == NULL || pos == -1)
    return false;

  if (pos == 2)
  {
    p->cont--;
    fseek(arq, p->np * sizeof(PAGINA), SEEK_SET);
    fwrite(p, sizeof(PAGINA), 1, arq);
    return true;
  }
  else
  {
    p->item[pos].chave = p->item[pos + 1].chave;
    p->item[pos].linkdir = p->item[pos + 1].linkdir;
    p->cont--;
    fseek(arq, p->np * sizeof(PAGINA), SEEK_SET);
    fwrite(p, sizeof(PAGINA), 1, arq);
    return true;
  }

  return false;
}

void sobeSucessor(int ch, FILE *arq, int raiz, int *chaveSucessor)
{
  int pos = -1;
  PAGINA *p = carregarPaginaChave(arq, ch, &pos, raiz);
  PAGINA *filha;

  if (p == NULL || pos == -1)
    return;

  filha = carregarPagina(arq, p->item[pos].linkdir);
  while (filha->item[0].linkdir > -1)
  {
    filha = carregarPagina(arq, filha->item[0].linkdir);
  }

  *chaveSucessor = filha->item[1].chave;

  p->item[pos].chave = filha->item[1].chave;
  fseek(arq, p->np * sizeof(PAGINA), SEEK_SET);
  fwrite(p, sizeof(PAGINA), 1, arq);
}

void moveParaEsquerda(FILE *arq, PAGINA *raiz, int posicaoRaiz)
{
  // TODO: escrever alterações em disco
  PAGINA *esquerda = carregarPagina(arq, raiz->item[posicaoRaiz - 1].linkdir);
  PAGINA *direita = carregarPagina(arq, raiz->item[posicaoRaiz].linkdir);

  esquerda->cont++;
  esquerda->item[esquerda->cont].chave = raiz->item[posicaoRaiz].chave;

  // os filhos da esquerda do primeiro elemento da página direita passa a ser os filhos da esquerda
  esquerda->item[esquerda->cont].linkdir = direita->item[0].linkdir;

  raiz->item[posicaoRaiz].chave = direita->item[1].chave;

  direita->item[0].linkdir = direita->item[1].linkdir;
  direita->cont--;

  for (int i = 1; i <= direita->cont; i++)
  {
    direita->item[i].chave = direita->item[i + 1].chave;
    direita->item[i].linkdir = direita->item[i + 1].linkdir;
  }

  // reescreve raíz
  fseek(arq, raiz->np * sizeof(PAGINA), SEEK_SET);
  fwrite(raiz, sizeof(PAGINA), 1, arq);

  // reescreve esquerda
  fseek(arq, esquerda->np * sizeof(PAGINA), SEEK_SET);
  fwrite(esquerda, sizeof(PAGINA), 1, arq);

  // reescreve direita
  fseek(arq, direita->np * sizeof(PAGINA), SEEK_SET);
  fwrite(direita, sizeof(PAGINA), 1, arq);
}

void moveParaDireita(FILE *arq, PAGINA *raiz, int posiscaoRaiz)
{
  PAGINA *direita = carregarPagina(arq, raiz->item[posiscaoRaiz].linkdir);
  PAGINA *esquerda = carregarPagina(arq, raiz->item[posiscaoRaiz - 1].linkdir);

  for (int i = direita->cont; i > 0; i--)
    direita->item[i + 1] = direita->item[i];
  direita->cont++;

  direita->item[1].linkdir = direita->item[0].linkdir;

  direita->item[1].chave = raiz->item[posiscaoRaiz].chave;

  raiz->item[posiscaoRaiz].chave = esquerda->item[esquerda->cont].chave;
  esquerda->cont--;

  // reescreve raíz
  fseek(arq, raiz->np * sizeof(PAGINA), SEEK_SET);
  fwrite(raiz, sizeof(PAGINA), 1, arq);

  // reescreve esquerda
  fseek(arq, esquerda->np * sizeof(PAGINA), SEEK_SET);
  fwrite(esquerda, sizeof(PAGINA), 1, arq);

  // reescreve direita
  fseek(arq, direita->np * sizeof(PAGINA), SEEK_SET);
  fwrite(direita, sizeof(PAGINA), 1, arq);
}

void combinaIrmaos(FILE *arq, PAGINA *raiz, int np)
{
  // Primeia coisa a ser feita é copiar a chave do separador no final do filho mais à esquerda.
  int posicaoSeparador;
  PAGINA *direita;
  PAGINA *esquerda;
  for (int i = 1; i <= 2; i++)
  {
    if (raiz->item[i].linkdir == np)
    {
      posicaoSeparador = i;
      esquerda = carregarPagina(arq, raiz->item[i - 1].linkdir);
      direita = carregarPagina(arq, np);
    }
  }

  esquerda->cont++;
  esquerda->item[esquerda->cont].chave = raiz->item[posicaoSeparador].chave;
  esquerda->item[esquerda->cont].linkdir = direita->item[0].linkdir;

  // Copiar as chaves e filhos do nó à direita para o nó à esquerda. Obs: importante ressaltar que as duas páginas irmãs contém 1 ou menos chaves
  esquerda->cont++;
  esquerda->item[esquerda->cont].chave = direita->item[1].chave;
  esquerda->item[esquerda->cont].linkdir = direita->item[1].linkdir;

  // Deslocar as chaves e filhos do pai uma posição para esuqerda (corrigindo o gap deixado pela exclusão).
  for (int i = posicaoSeparador; i < raiz->cont; i++)
  {
    raiz->item[i].chave = raiz->item[i + 1].chave;
    raiz->item[i].linkdir = raiz->item[i + 1].linkdir;
  }

  raiz->cont--;

  // exclusão da página da direita
  direita->cont = 0;
  fseek(arq, direita->np * sizeof(PAGINA), SEEK_SET);
  fwrite(direita, sizeof(PAGINA), 1, arq);

  fseek(arq, raiz->np * sizeof(PAGINA), SEEK_SET);
  fwrite(raiz, sizeof(PAGINA), 1, arq);

  fseek(arq, esquerda->np * sizeof(PAGINA), SEEK_SET);
  fwrite(esquerda, sizeof(PAGINA), 1, arq);
}

// Função que restaura a árvore aplicando as regras de underflow, realizando as distribuições necessárias e/ou concatenações.

void restauraArvore(FILE *arq, PAGINA *raiz, PAGINA *p)
{
  // Caso em que a página com underflow é a mais à esquerda
  if (p->np == raiz->item[0].linkdir)
  {
    if (carregarPagina(arq, raiz->item[1].linkdir)->cont > 1)
      moveParaEsquerda(arq, p, 1); // move o irmão 1 para o irmão 0
    else
      combinaIrmaos(arq, raiz, raiz->item[1].linkdir); // concatenação com a raiz (combina o irmão a direia + p + raiz)
  }
  else
  {
    // verifica se é o mais a direita
    if (p->np == raiz->item[2].linkdir)
    {
      if (carregarPagina(arq, raiz->item[1].linkdir)->cont > 1)
        moveParaDireita(arq, raiz, raiz->item[1].linkdir); // move do irmao do meio para o da direita
      else
        combinaIrmaos(arq, raiz, p->np); // concatenação. Obs: ao invés do p->np poderia ser o próprio raiz->item[2].linkdir, uma vez que se caiu nesse trecho do código é porque são iguais. Entretanto preferi colocar p->np para reforçar que esse método de concatenação pega do irmão mais à direita, nesse caso o próprio p, em relação às duas páginas a serem concatenadas.
    }
    else
    {
      // caso em que a pagina está no meio
      if (carregarPagina(arq, raiz->item[0].linkdir)->cont > 1)
        moveParaDireita(arq, raiz, raiz->item[0].linkdir);
      else if (carregarPagina(arq, raiz->item[2].linkdir)->cont > 1)
        moveParaEsquerda(arq, p, 2);
      else                                               // nenhum dos dois irmaos pode emprestar
        combinaIrmaos(arq, raiz, raiz->item[1].linkdir); // concatenação. Obs: Estou passando a página do meio, pois para a concatenação deve ser passado sempre a página mais a direita relativa às duas páginas que serão concatenadas.
    }
  }
}

bool buscarChaveNaPagina(PAGINA pagina, int chave, int *posicao)
{
  if (chave < pagina.item[1].chave)
  {
    *posicao = 0;
    return false;
  }

  for (int i = 1; i <= pagina.cont; i++)
  {
    if (pagina.item[i].chave == chave)
    {
      *posicao = i;
      return true;
    }
  }

  return false;
}

// Função baseada no icmc
void excluir(char nomearq[], int *raiz, int ch)
{
  if (*raiz == -1 || ch < 0)
    return;
  PAGINA *pai;
  FILE *arq = fopen(nomearq, "rb+");
  rewind(arq);
  int posicaoChavePagina;
  PAGINA *p = carregarPagina(arq, *raiz);

  if (buscarChaveNaPagina(*p, ch, &posicaoChavePagina))
  {
    // se for folha
    if (p->item[0].linkdir == -1 && p->item[1].linkdir == -1 && p->item[2].linkdir == -1)
    {
      if (!removeChave(arq, p->item[posicaoChavePagina].chave, *raiz))
        return;
    }
    else
    {
      int chaveSucessor = -1;
      sobeSucessor(ch, arq, *raiz, &chaveSucessor);
      pai = p;
      excluir(nomearq, &p->item[posicaoChavePagina].linkdir, chaveSucessor);
    }
  }
  else
  {
    int i;
    for (i = p->cont; ch < p->item[i].chave; i--)
      ;
    pai = p;
    excluir(nomearq, &p->item[i].linkdir, ch);
  }

  // Verificações da regra de underflow
  // Na volta da recursão vamos corrigindo os "problemas" deixados para trás
  p = carregarPagina(arq, *raiz);
  if (p != NULL)
  {
    if (p->cont < 1)
    {

      restauraArvore(arq, pai, p); // Nesse caso a raiz terá um valor diferente para cada recursão. Ela representa a "raiz relativa" dentro da recursão

      if (carregarPagina(arq, 0)->cont == 0)
        *raiz = -1;
    }
  }

  fclose(arq);
}

int main()
{

  /* =========================== Página 0 ========================================== */
  // raiz
  int raiz = 0;
  PAGINA p1;
  p1.np = 0;
  p1.cont = 1;

  CHLINK c1;
  c1.chave = -1;
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
  /* ================================================================================ */

  /* =========================== Página 1 ========================================== */
  PAGINA p2;
  p2.np = 1;
  p2.cont = 2;

  CHLINK c3;
  c3.chave = -1;
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
  /* ================================================================================ */

  /* =========================== Página 2 ========================================== */
  PAGINA p3;
  p3.np = 2;
  p3.cont = 2;

  CHLINK c6;
  c6.chave = -1;
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

  /* ================================================================================ */

  /* =========================== Página 3 ========================================== */
  PAGINA p4;
  p4.np = 3;
  p4.cont = 2;
  CHLINK c9;
  c9.chave = -1;
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
  /* ================================================================================ */

  /* =========================== Página 4 ========================================== */
  PAGINA p5;
  p5.np = 4;
  p5.cont = 2;
  CHLINK c12;
  c12.chave = -1;
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
  /* ================================================================================ */

  /* =========================== Página 5 =============================================== */
  PAGINA p6;
  p6.np = 5;
  p6.cont = 2;
  CHLINK c15;
  c15.chave = -1;
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
  /* ==================================================================================== */

  /* =========================== Página 6 =============================================== */
  PAGINA p7;
  p7.np = 6;
  p7.cont = 2;
  CHLINK c18;
  c18.chave = -1;
  c18.linkdir = -1;
  CHLINK c19;
  c19.chave = 15;
  c19.linkdir = -1;
  CHLINK c20;
  c20.chave = 16;
  c20.linkdir = -1;
  p7.item[0] = c18;
  p7.item[1] = c19;
  p7.item[2] = c20;
  /* ===================================================================================== */

  /* =========================== Página 7 =============================================== */
  PAGINA p8;
  p8.np = 7;
  p8.cont = 2;
  CHLINK c21;
  c21.chave = -1;
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
  /* ===================================================================================== */

  /* =========================== Página 8 =============================================== */
  PAGINA p9;
  p9.np = 8;
  p9.cont = 2;
  CHLINK c24;
  c24.chave = -1;
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
  /* ===================================================================================== */

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

  // 1.
  printf("TESTE %i: \n", 1);
  excluir((char *)"arvore-b.bin", &raiz, 3);
  imprimirArvore(arq, raiz);
  printf("\n\n");
  // Resultado Esperado 13,4,8,17,21,1,5,6,9,10,15,16,18,19,23,26

  // 2.
  printf("TESTE %i: \n", 2);
  excluir((char *)"arvore-b.bin", &raiz, 19);
  imprimirArvore(arq, raiz);
  printf("\n\n");
  // Resultado Esperado 13,4,8,17,21,1,5,6,9,10,15,16,18,23,26

  // 3.
  printf("TESTE %i: \n", 3);
  excluir((char *)"arvore-b.bin", &raiz, 4);
  imprimirArvore(arq, raiz);
  printf("\n\n");
  // Resultado Esperado 13,5,8,17,21,1,6,9,10,15,16,18,23,26

  // 4. Teste com chave que não existe
  printf("TESTE %i: \n", 4);
  excluir((char *)"arvore-b.bin", &raiz, 56);
  imprimirArvore(arq, raiz);
  printf("\n\n");
  // Resultado Esperado 13,5,8,17,21,1,6,9,10,15,16,18,23,26

  // 5.
  printf("TESTE %i: \n", 5);
  excluir((char *)"arvore-b.bin", &raiz, 1);
  imprimirArvore(arq, raiz);
  printf("\n\n");
  // Resultado Esperado 13,8,17,21,5,6,9,10,15,16,18,23,26

  // 6. Teste com chave que não existe
  printf("TESTE %i: \n", 6);
  excluir((char *)"arvore-b.bin", &raiz, -7);
  imprimirArvore(arq, raiz);
  printf("\n\n");
  // Resultado Esperado 13,8,17,21,5,6,9,10,15,16,18,23,26

  // 7.
  printf("TESTE %i: \n", 7);
  excluir((char *)"arvore-b.bin", &raiz, 13);
  imprimirArvore(arq, raiz);
  printf("\n\n");
  // Resultado Esperado 15,8,17,21,5,6,9,10,16,18,23,26
  /*
    //8.
    printf("TESTE %i: \n", 8);
    excluir("arvore-b.bin", &raiz, 9);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado 15,8,17,21,5,6,10,16,18,23,26

    //9.
    printf("TESTE %i: \n", 9);
    excluir("arvore-b.bin", &raiz, 16);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado 15,8,21,5,6,10,17,18,23,26

    //10.
    printf("TESTE %i: \n", 10);
    excluir("arvore-b.bin", &raiz, 23);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado 15,8,21,5,6,10,17,8,26

    //11.
    printf("TESTE %i: \n", 11);
    excluir("arvore-b.bin", &raiz, 21);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado 15,8,18,5,6,10,17,26

    //12.
    printf("TESTE %i: \n", 12);
    excluir("arvore-b.bin", &raiz, 18);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado 15,8,17,26,5,6,10

    //13.
    printf("TESTE %i: \n", 13);
    excluir("arvore-b.bin", &raiz, 5);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado 15,8,17,26,6,10

    //14.
    printf("TESTE %i: \n", 14);
    excluir("arvore-b.bin", &raiz, 8);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado 15,16,10,17,26

    //15. Chave que não existe
    printf("TESTE %i: \n", 15);
    excluir("arvore-b.bin", &raiz, -1);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado -1

    //16.
    printf("TESTE %i: \n", 16);
    excluir("arvore-b.bin", &raiz, 15);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado 17,6,10,26

    //17.
    printf("TESTE %i: \n", 17);
    excluir("arvore-b.bin", &raiz, 10);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado 17,6,26

    //18.
    printf("TESTE %i: \n", 18);
    excluir("arvore-b.bin", &raiz, 17);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado 6,26

    //19.
    printf("TESTE %i: \n", 19);
    excluir("arvore-b.bin", &raiz, 26);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado 6

    //20. Arvore esvaziada
    printf("TESTE %i: \n", 20);
    excluir("arvore-b.bin", &raiz, 6);
    imprimirArvore(arq, raiz);
    printf("\n\n");
    //Resultado Esperado -1
    */

  fclose(arq);
}