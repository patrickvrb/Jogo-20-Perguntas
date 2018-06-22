#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "headers.h"

/**@brief Teste para verificar nao quebra do programa
* Ao tentar desalocar um nó ja nulo, o programa segue normalmente.
*/

TEST_CASE ("Remover no ja nulo", "Nao gera erros de memoria")
{
  arvore *no = NULL;
  removerNo(no);
  REQUIRE(no == NULL);
}

/**@brief Teste parar verificar a correta funcionalidade da funcao preencherNo.
* O teste realiza a chamada da funcao preencherNo com parametros criados,
*retornando seu valor em uma variavel do tipo arvore.
*/

TEST_CASE( "No != NULL", "Assegurar alocacao e preenchimento do no" ){

    arvore *no = NULL;
    int indice=1;
    char pergunta[7] = "Olá?";
    no = preencherNo(pergunta,indice);

    REQUIRE(no!=NULL);
    REQUIRE(no->Sim == NULL);
    REQUIRE(no->Nao == NULL);
    REQUIRE(no->pergunta == pergunta);
    REQUIRE(no->indice == indice);
}


/**@brief Teste parar verificar a correta funcionalidade da funcao carregarArvore.
*
*/
TEST_CASE("Carregamento"," Assegurar carregamento de arvore em memoria"){

  FILE *pArquivo;
  pArquivo = fopen("perguntas.txt", "r+");

  arvore *raiz = (arvore *)malloc(sizeof(arvore));
  raiz->Sim = NULL;
  raiz->Nao = NULL;
  raiz->indice = 1;
  arvore *salvar = NULL;
  salvar = carregarArvore(pArquivo, &raiz->Sim, &raiz, 2, 1);

  REQUIRE(salvar != NULL);
  REQUIRE(salvar->Sim != NULL);
  REQUIRE(salvar->Nao == NULL);
  REQUIRE(salvar->indice == 1);
  fclose(pArquivo);
}

/**@brief Teste parar verificar a correta funcionalidade da funcao carregarArvore.
*
*/

TEST_CASE("Percorrer com resposta invalida (3) "," O programa nao realiza o percorrimento e mantem seu estado original")
{

  FILE *pArquivo;
  pArquivo = fopen("perguntas.txt", "r+");

  arvore *raiz = (arvore *) malloc(sizeof(arvore));
  raiz->Sim = NULL;
  raiz->Nao = NULL;
  raiz->indice = 1;
  arvore *salvar = NULL;
  salvar = carregarArvore(pArquivo, &raiz->Sim, &raiz, 2, 1);
  percorrer(3, &salvar);
  REQUIRE(salvar != NULL);
  REQUIRE(salvar->Sim != NULL);
  REQUIRE(salvar->Nao == NULL);
  REQUIRE(salvar->indice == 1);
  fclose(pArquivo);
}

TEST_CASE("Preencher com nó vazio", "Programa não aloca memória e mantém seu estado")
{
  arvore *no = NULL;
  char * pergunta = NULL;
  no = preencherNo(pergunta, 1);
  REQUIRE(no == NULL);
}
