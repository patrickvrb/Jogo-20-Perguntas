#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "headers.h"


TEST_CASE ("Remover no ja nulo", "Nao gera erros de memoria")
{
  arvore *no = NULL;
  removerNo(no);
  REQUIRE(no == NULL);
}
/* Teste parar verificar a correta funcionalidade da funcao preencherNo*/

TEST_CASE( "No != NULL", "Assegurar alocacao e preenchimento do no" ){

    arvore *no = NULL;
    int indice=1;
    char * pergunta;
    pergunta = (char*)malloc(50*sizeof(char));
    no = preencherNo(pergunta,indice);

    REQUIRE(no!=NULL);
    REQUIRE(no->Sim == NULL);
    REQUIRE(no->Nao == NULL);
    REQUIRE(no->indice == indice);
}

/* Teste parar verificar a correta funcionalidade da funcao carregarArvore*/
TEST_CASE("Carregamento"," Assegurar carregamento de arvore em memoria"){

  FILE *pArquivo;
  pArquivo = fopen("perguntas.txt", "r+");

  arvore *raiz = (arvore *) malloc(sizeof(arvore));
  raiz->Sim = NULL;
  raiz->Nao = NULL;
  raiz->indice = 1;
  arvore *salvar = NULL;
  salvar = carregarArvore(pArquivo, &raiz->Sim, &raiz, 2, 1);

  REQUIRE(salvar != NULL);
  REQUIRE(salvar->Sim != NULL);
  REQUIRE(salvar->Nao == NULL);
  REQUIRE(salvar->indice == 1);
}
