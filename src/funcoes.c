#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    char pergunta[50];
    int indice;
    struct no *Sim;             //Nó Esquerda
    struct no *Nao;             //Nó Direita
} arvore;

arvore *preencherNo(char *pergunta, int indice){
    arvore *no = (arvore*)malloc(sizeof(arvore));
    strcpy(no->pergunta, pergunta);
    no->indice = indice;
    no->Sim = NULL;
    no->Nao = NULL;
    return no;
}

void removerNo(arvore *no){
    if(no!=0){
        removerNo(no->Sim);
        removerNo(no->Nao);
        free(no);
    }
}