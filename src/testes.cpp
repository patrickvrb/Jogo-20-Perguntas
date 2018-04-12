#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "headers.h"

TEST_CASE( "No != NULL", "Assegurar alocacao e preenchimento do no" ){

    arvore *no = NULL;
    int indice=1;
    char * pergunta;
    pergunta = (char*)malloc(50*sizeof(char));
    no = preencherNo(pergunta,indice);

    REQUIRE(no!=NULL);
}

TEST_CASE("Carregar Arvore","Carregar Arvore"){

  FILE *pArquivo;
  pArquivo = fopen("perguntas.txt", "r+");

  arvore *raiz = (arvore *) malloc(sizeof(arvore));
  raiz->Sim = NULL;
  raiz->Nao = NULL;
  raiz->indice = 1;
  arvore *salvar = NULL;
  salvar = carregarArvore(pArquivo, &raiz->Sim, &raiz, 2, 1);

  REQUIRE(salvar != NULL);
}
