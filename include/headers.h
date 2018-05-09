#include <stdio.h>

/***** Estrutura do nó da Árvore
* Assertiva estrutural:
* A árvore binária, como na estrutura abaixo, possui critérios 
*como: possuir nó máximo dois filhos por nó,
*os apontadores dos nós existentes só podem apontar para
*nós do tipo árvore ainda não presentes na árvore, ou seja, novos
*nós. Além disso, os lados direito e esquerdo de cada nó e suas
*respectivas árvores são disjuntos.
*
* no != NULL => indice > 0
* no != NULL => *pergunta != NULL
* no != NULL => no *Sim é ponteiro para outro nó do tipo árvore
* no != NULL => no *Nao é ponteiro para outro nó do tipo árvore
*/


typedef struct no{
    char pergunta[50];
    int indice;
    struct no *Sim;             //Nó Esquerda
    struct no *Nao;             //Nó Direita
} arvore;


/**************************** * Função: Preencher nó da árvore
* Variáveis:
* 	 *pergunta: ponteiro (CHAR) para vetor contendo a pergunta
*	 indice: inteiro utilizado para indexar árvore
*	 no: retorno do tipo árvore, contendo endereço do nó
*	*pergunta e indice compõem a interface explícita da função
* Assertiva de entrada
*    *pergunta != NULL
* 	 indice >= 0
* Assertiva de saída
*	 no != NULL
*	 no tipo árvore
*****************************/
arvore *preencherNo(char *pergunta, int indice);


/**************************** * Função: remover e desalocar nó da árvore
* Variáveis:
* 	 *no: ponteiro (ARVORE) contendo o nó da árvore
*	 *no compõe a interface explícita da função
* Assertiva de entrada
*    *no != NULL
* Assertiva de saída
*	 no == NULL
*****************************/
void removerNo(arvore *no);


/**************************** * Função: Salvar árvore em arquivo .txt
* Variáveis:
* 	 *salvar: ponteiro (ARVORE) contendo a árvore a ser salvada
*	 *pSalvar: ponteiro (FILE) contendo o arquivo em que a árvore
*			  será salvada
*	*salvar compõe a interface explícita da função
*	*pSalvar compõe a interface implícita da função
* Assertiva de entrada
*    *salvar != NULL
* 	 *pSalvar != NULL
* Assertiva de saída
*	 Nenhuma saída gerada em variável, sendo apenas modificado o
*	 arquivo com a árvore salvada.
*****************************/
void salvarArvore(arvore *salvar, FILE *pSalvar);


/**************************** * Função: Carregar a árvore de arquivo
*										para memória
* Variáveis:
* 	 *pArquivo: ponteiro (FILE) contendo o arquivo a ser lido
*	 **salvar: ponteiro (ARVORE) para referência de um filho da árvore
*	 **pai: ponteiro (ARVORE) para referência da raíz da árvore
*    indice: inteiro contendo o índice do elemento a ser carregado
*    direcao: inteiro representando sentido direita ou esquerda da árvore
*	 *pArquivo compõe a interface implícita da função
*	 Os parâmetros restantes acima compõem a interface explícita da função
* Assertiva de entrada
*    *pArquivo != NULL
* 	 **salvar != NULL
*	 **pai != NULL
*	 indice >= 0
*	 direcao == 0 || direcao == 1
* Assertiva de saída
*	 *pai != NULL 
*****************************/
arvore *carregarArvore(FILE *pArquivo, arvore **salvar, arvore **pai, int indice, int direcao);


/**************************** * Função: Percorrer Árvore Binária
* Variáveis:
* 	 resp: inteiro contendo a resposta dada pelo usuário
*	 **raiz: ponteiro (ARVORE) para referência da raiz da árvore
*	 resp e **raiz compõem a interface explícita da função
* Assertiva de entrada
*    resp == 0 || resp == 1
* 	 **raiz =! NULL
* Assertiva de saída
*	 no->Sim != NULL || no->Não != NULL
*****************************/
arvore *percorrer(int resp, arvore **raiz);


/**************************** * Função: Inicializar jogo
* Variáveis:
*	 **raiz: ponteiro (ARVORE) para referência da raiz da árvore
*	 *pSalvar: ponteiro (FILE) para o arquivo a ser salvado
*	 **raiz compõe a interface explícita da função
*	 *pSalvar compõe a interface implícita da função
* Assertiva de entrada
* 	 **raiz != NULL
*	 *pSalvar != NULL
* Assertiva de saída
*	 Nenhuma saída gerada em variável
*****************************/
void novoJogo(arvore **raiz, FILE *pSalvar);
