#include <stdio.h>
#include <malloc.h>
//encontrar caminho mais curto
void buscaLargura(VERTICE* g, int i, int t){
    FILA f;
    inicializarFIla(&f);
    zerarFlags(g);
    zerarVia(g);
    g[i].flag = 1;
    entrarFila(&f, i);
    while(f.inicio){
        i = sairFila(&f);
        p = g[i].inicio;
        while(p){
            if(g[p->v].flag == 0){
                g[p->v].flag = 1;
                entrarFila(&f, p->v);
                g[p->v].via = i;
            }
            p = p->prox;
        }
    }
}

//encontrar o caminho até t e parar
void buscaLargura(VERTICE* g, int i, int t){
    FILA f;
    inicializarFIla(&f);
    zerarFlags(g);
    zerarVia(g);
    g[i].flag = 1;
    entrarFila(&f, i);
    while(f.inicio){
        i = sairFila(&f);
        p = g[i].inicio;
        while(p){
            if(g[p->v].flag == 0)
                g[p->v].flag = 1;
            entrarFila(&f, p->v);
            g[p->v].via = i;
            if(p->v == t){
                while(f.inicio)
                    sairFila(&f);
                return;
            }
            p = p->prox;
        }
    }
}

//Encontrar distancia
void buscaLargura(VERTICE* g, int i, int t){
    FILA f;
    inicializarFIla(&f);
    zerarFlags(g);
    zerarVia(g);
    zeraDist(g);
    g[i].flag = 1;
    entrarFila(&f, i);
    while(f.inicio){
        i = sairFila(&f);
        p = g[i].inicio;
        while(p){
            if(g[p->v].flag == 0)
                g[p->v].flag = 1;
            entrarFila(&f, p->v);
            g[p->v].via = i;
            g[p->v].dist = 1 + g[i].dist;
            if(p->v == t){
                while(f.inicio)
                    sairFila(&f);
                return;
            }
            p = p->prox;
        }
    }
}


/*
Problema: 

Seja um grafo ...
Exibir todos os vértices alcançáveis a partir de i que estão até m arestas de distância

*/

void exibirCaminhoMaisCurto(VERTICE* g, int i, int t){
    buscaLargura(g, i, t);
    int x = t;
    while(x > 0){
        printf("%d", x);
        x = g[x].via;
    }
}

/*
Achar o numero de grupos
*/
int Contargrupos(VERTICE* g, int V){
    int grupos = 0;
    i = 1;
    zerarflags(g);
    grupos = 0;
    for(i = 1; i <= V; i++){
        if(g[i].flag == 0){
            buscaProf(g, i); 
            grupos = grupos + 1;
        }
    }
    return grupos;
}


/*
Encontre o amigo direto ou indireto
que receber maior nro de likes

Passos:
(1) O que são os vértices e as arestas?

(2) Informações do problema?

(3) Precisa de Busca?

(4) Se sim, qual?

Para esse problema...
- Computar os vértices alcançáveis (busca)
- Dentre os vértices visitados, selecionar o de maior grau de entrada
*/

NO* maisLikes(VERTICE* g, int i){
    busca(g, i);
    int maiorGrau = -1;
    int maisLikes = 0;
    int ge;
    int i;
    for(i = 1; i <= V; i++){
        if(g[i].flag == 2){
            ge = grauEntrada(g, i);
            if(ge > maiorGrau){
                maiorGrau = ge;
                maisLikes = i;
            } 
        }
    }
    return g[i].inicio;
}





/*

Ex: Seja um grafo g em lista de adjacencia
representando a rede de amigos diretos
ou indiretos de um usuário u1
E seja um grafo m em matriz de adjacencias 
representando a rede de um usuário u2

(a) Qual deles possui mais amigo?
(b) eles possuem os mesmos amigos?

*/

void acharAmigos(int m[V][V], int u2, int flags[v]){
    FILA f;
    inicializarFIla(&f);
    zerarFlags(flags);
    flags[u2] = 1;
    entrarFila(&f, u2);
    while(f.inicio){
        i = sairFila(&f);
        int j;
        for(j = 1; j <= V; j++){
            if(m[i][j] == 1 && flags[j] == 0){
                entrarFila(&f, j);
                flags[j] = 1;
            }
        }
        flags[i] = 2;
    }
}
