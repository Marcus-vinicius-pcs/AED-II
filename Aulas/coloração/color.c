void colorirProfundidade(VERTICE* g, int i, int cor[], int* k){
    if(cor[i] == 0){
        cor[i] = acharCor(g, i, *cor, k); //pega a menor cor possível que não está sendo utilizada ainda
        NO* p = g[i].inicio
        while(p){
            colorirProfundidade(g, p->v, cor, k);
            p = p->prox;
        }
    }
}

//utilizando a busca em largura
//pendente implementação


