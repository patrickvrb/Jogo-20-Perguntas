#include <stdio.h>

typedef struct no{
    char pergunta[50];
    int indice;
    struct no *Sim;             //Nó Esquerda
    struct no *Nao;             //Nó Direita
} arvore;