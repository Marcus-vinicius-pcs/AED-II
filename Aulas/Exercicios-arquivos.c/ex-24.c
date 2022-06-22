/*
Um determinado departamento x foi excluído, e todos os funcionários a que ele pertencia foram realocados
para o departamento y. Escreva um algoritmo que atualize ambos os arquivos e os respectivos índices. 
Considere para este fim que as funções de manipulação de índices vistas em aula já estão implementadas.

bool inserirIndice(tabela, id, end);
int buscarIndice(tabela, id);
int exlcluirIndice(tabela, id);
*/

#include <stdio.h>

typedef struct 
{
    int cpf
} empregados;

typedef struct 
{
    int codigo;
} departamentos;



