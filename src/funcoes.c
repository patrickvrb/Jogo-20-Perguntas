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

void salvarArvore(arvore *salvar, FILE *pSalvar){

    char *aux;

    aux = (char*)malloc(4*(sizeof(char)));
    sprintf(aux, "%d", salvar->indice);
    fprintf(pSalvar, "%s", aux);
    fprintf(pSalvar, "%c", ')');
    fprintf(pSalvar, "%s", salvar->pergunta);
    fprintf(pSalvar, "%c", '\n');

    free(aux);

    if(salvar->Sim != NULL){
        salvarArvore(salvar->Sim, pSalvar);
    }

    if(salvar->Nao != NULL){
        salvarArvore(salvar->Nao, pSalvar);
    }
}

arvore *carregarArvore(FILE *pArquivo, arvore **salvar, arvore **pai, int indice, int direcao){

    int indiceArquivo;
    char *numero = (char*)malloc(4*(sizeof(char)));
    char *pergunta = (char*)malloc(50*(sizeof(char)));
    char *aux = (char*)malloc(2*(sizeof(char)));

    rewind(pArquivo);                              //Volta pro inicio do Arquivo p/ recursividade

    while(!feof(pArquivo)){
        fscanf(pArquivo, "%4[^)])", numero);
        indiceArquivo = atoi(numero);
        if(indiceArquivo == indice){               //Avalia se chegou na pergunta certa
            fscanf(pArquivo, "%50[^\n]\n", pergunta);
            *salvar = preencherNo(pergunta, indice);
            carregarArvore(pArquivo, &(*salvar)->Sim, salvar,(((*salvar)->indice)*2), 1);
        }
        else fscanf(pArquivo, "%50[^\n]\n", aux);
    }

    free(numero);
    free(pergunta);
    free(aux);

    if(direcao == 1) {
        carregarArvore(pArquivo, &(*pai)->Nao, pai,((((*pai)->indice)*2) + 1) , 0);
    }

    return *pai;

}
