/*

Procedimento:

1 - dist de s é 0
  - via permanece -1
  - s é inserido em p

2 - Faça z = s
2.a - Inserir z em p

3 - Para cada adjacente de z que não está em p, verifica se há dist > dist atual, e se houver substitui dist e via

4 - Escolher um novo z tal que não esteja em p, e tenha um menor dist possível

5 - Repetir o passo 3

Criar uma fila de prioridades -> Estrutura de dados auxiliar

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct adj {
	int tipo;
	int custo;
	int v;
	struct adj* prox;
} NO;

// vertices
typedef struct {
	NO* inicio;
  int vertices;
} VERTICE;

VERTICE *inicializaGrafo(int V)
{

    //DUVIDA: os tipos de cidade serão iniciadas nessa função?
    VERTICE *g = (VERTICE *)malloc(sizeof(VERTICE) * V);
    for (int i = 0; i < V; i++)
    {
        NO *p = (NO *)malloc(sizeof(NO));
        p->prox = NULL;
		p->v = i;
        g[i].inicio = p;
    }
    g->vertices = V;
    return g;
}

NO *buscaAresta(VERTICE *g, int i, int j, NO **ant)
{
    NO *p = g[i].inicio->prox;
    while (p)
    {
        if (p->tipo == j)
        {
            return p;
        }
        *ant = p;
        p = p->prox;
    }
    return NULL;
}

bool insereArestaPonderada(VERTICE *g, int i, int j, int c)
{ /*
     NO *ant;
     NO *atual = buscaAresta(g, i, j, &ant);
     if (atual)
         return false;*/
    NO *atual = (NO *)malloc(sizeof(NO));
    atual->v = j;
    atual->prox = g[i].inicio->prox;
    atual->custo = c;
    g[i].inicio->prox = atual;
    return true;
}

void inicializaD(VERTICE* g, int *dist, int *predecessor, int source){
    for(int v = 0; v < g->vertices; v++){
        dist[v] = 1000; //Nesse caso 1000 simboliza infinito
        predecessor[v] = -1;
    }
    dist[source] = 0;
}

void relaxa(VERTICE* g, int *dist, int *pred, int u, int v){
    NO* adj = g[u].inicio->prox;
    while(adj && adj->v != v)
        adj = adj->prox;
    if(adj){
        if(dist[v] > dist[u] + adj->custo) {
            dist[v] = dist[u] + adj->custo;
            pred[v] = u;
        }
    }
}

bool existeAberto(VERTICE* g, int *aberto){
    for(int i = 0; i < g->vertices; i++)
        if(aberto[i] == 1) return true;
    return false;
}

int menorDist(VERTICE* g, int* aberto, int *dist){
    int i;
    for(i = 0; i < g->vertices; i++)
        if(aberto[i]) break;
    if(i == g->vertices) return (-1);
    int menor = i;
    for(i = menor + 1; i < g->vertices; i++)
        if(aberto[i] && dist[menor] > dist[i])
            menor = i;
    return menor;
}

int *dijkstra(VERTICE* g, int source){
    int* dist = (int*) malloc(sizeof(int));
    int pred[g->vertices];
    int aberto[g->vertices];
    inicializaD(g, dist, pred, source);

    for(int i = 0; i < g->vertices; i++)
        aberto[i] = 1;

    while(existeAberto(g, aberto)) {
        int u = menorDist(g, aberto, dist);
        aberto[u] = 0;
    

        NO* adj = g[u].inicio->prox;
        while(adj){
            relaxa(g, dist, pred, u, adj->v);
            adj = adj->prox;
        }
    }
    return(dist);
}

int main()
{

	VERTICE *g = inicializaGrafo(5);
	g[0].inicio->tipo = 1;
	g[1].inicio->tipo = 1;
	g[2].inicio->tipo = 1;
	g[3].inicio->tipo = 2;
	g[4].inicio->tipo = 3;
	insereArestaPonderada(g, 0, 1, 4);
	insereArestaPonderada(g, 0, 2, 2);
	insereArestaPonderada(g, 0, 3, 1);
	insereArestaPonderada(g, 2, 1, 3);
	insereArestaPonderada(g, 3, 2, 3);
	insereArestaPonderada(g, 4, 0, 2);
	insereArestaPonderada(g, 4, 3, 4);

	for (int i = 0; i < 5; i++)
    {
        NO *p = g[i].inicio->prox;
        printf("[%i] ", g[i].inicio->v);
        while (p)
        {
            printf("%i ", p->v);
            p = p->prox;
        }
        printf("\n\n");
    }

  int *r = dijkstra(g, 0);
  int i;
  for(i = 0; i < 5; i++){
    printf("D(v0 -> v%d) = %d\n", i, r[i]);
  }
}