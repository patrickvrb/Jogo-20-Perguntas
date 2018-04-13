#include <stdio.h>

typedef struct no{
    char pergunta[50];
    int indice;
    struct no *Sim;             //Nó Esquerda
    struct no *Nao;             //Nó Direita
} arvore;

arvore *preencherNo(char *pergunta, int indice);

void removerNo(arvore *no);

void salvarArvore(arvore *salvar, FILE *pSalvar);

arvore *carregarArvore(FILE *pArquivo, arvore **salvar, arvore **pai, int indice, int direcao);

arvore *percorrer(int resp, arvore **raiz);

void novoJogo(arvore **raiz, FILE *pSalvar);