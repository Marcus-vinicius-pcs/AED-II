/*
1. Listas Sequenciais

*/

int t = sizeof(int);
int lista[MAX];
//Escrita (versão com nroelem)
fwrite(&nroelem, t, 1, arq);
fwrite(lista, t, nroelem, arq);

//Leitura (Versão sem nroelem)
int lista[MAX];
int nroElm = fread(lista, t, MAX, arq);

//Listas Ligadas
NO* p = l->inicio;
whlie(p){
    fwrite(p->chave, t, 1, arq);
    //fpritnf(arq, "%d", p->chave)
    p = p->prox;
}

LISTA l;
inicializa(&l);
NO* fim = NULL;
int chave;
while(1 == fread(&chave, t, 1, arq)){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->chave = chave;
    novo->prox = NULL;
    if(fim){
        fim->prox = novo;
    } else {
        l->inicio = novo;
    }
    fim = novo;
}

//4. Arvores Binarias
emordem(p->esq);
fwrite(&(p->chave));
emordem(p->dir);

//5.grafos
fwrite(&V, t, 1, arq){
    int i;
    for(i = 0; i <= V; i++){
        NO* p = g[i].inicio;
        while(p){
            int origem = i;
            int destino = p->v;
            int peso = p->peso;
            fwrite(&origem, t, 1, arq);
            fwrite(&destino, t, 1, arq);
            fwrite(&peso, t, 1, arq);
            p = p->prox;
        }
    }
}


VERTICE* g;
int V;
fread(&V, t, 1, arq);
g = (VERTICE*)malloc(sizeof(int) * V);
inicializa(g);
int origem, dest, peso;
while(1 == fread(&origem, t, 1, arq)){
    fread(&dest, t, 1, arq);
    fread(&peso, t, 1, arq);
    insereAresta(g, origem, dest, peso);
}

void insereAresta(VERTICE*g, int origem, int dest, int peso){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->p = dest;
    novo->peso = peso;
    novo->prox = g[origem].inicio;
    g[origem].inicio = novo;
}
