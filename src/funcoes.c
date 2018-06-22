#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**@brief Estrutura de criação do No padrao da arvore.
*A estrutura possui um campo para o texto (pergunta) de tamanho 50,
*um capo para o índice do nó da ávore, utilizado para reestruturação
*da árvore, e dois ponteiros para os possíveis nós filhos
*/
typedef struct no{
    char pergunta[50];
    int indice;
    struct no *Sim;             //Nó Esquerda
    struct no *Nao;             //Nó Direita
} arvore;

/**@brief Funcao para criar um no novo e preenchido, baseado nos parametros.
*A função recebe como parâmetro um ponteiro com o texto da pergunta
*a ser colocado no novo nó da árvore, que é alocado também nessa função
*/
arvore *preencherNo(char *pergunta, int indice){
    assert(pergunta != NULL);
    assert(indice >= 0);
    arvore *no = (arvore*)malloc(sizeof(arvore));
    if(no == NULL) printf("Falha ao alocar memória!! \n");
    strcpy(no->pergunta, pergunta);
    no->indice = indice;
    no->Sim = NULL;
    no->Nao = NULL;
    return no;
}

/**@brief Funcao remover o no atual.
*A função desaloca recursivamente a árvore contida abaixo até o nó recebido
*como parâmetro, realizando uma checagem inicial de sua existência
*/
void removerNo(arvore *no){
    if(no!=0){
        removerNo(no->Sim);
        removerNo(no->Nao);
        free(no);
    }
}

/**@brief Função para salvar a arvore em um arquivo .txt.
* A função recebe como parâmetros o ponteiro da arvore a ser
*salvada, bem como o ponteiro do arquivo qual será utilizado
*para isso.
* Para salvar, é utilizado a função fprintf com os dados lidos
*da árvore, na forma INDICE ) PERGUNTA \n
* Ao final, é realizada a checagem de ambos ponteiros do nó atual,
*para realizar a chamada recursiva da função e salvar a árvore na ordem
*correta. O ponteiro auxiliar é desalocado ao fim de seu uso
*/
void salvarArvore(arvore *salvar, FILE *pSalvar){

    assert(salvar != NULL);
    assert(pSalvar != NULL);
    char *aux;

    aux = (char*)malloc(4*(sizeof(char)));
    if(aux == NULL) printf("Falha ao alocar memória!! \n");

    sprintf(aux, "%d", salvar->indice);

  //Impressao padronizada no arquivo .txt, utilizando ')' e \n como separadores
    fprintf(pSalvar, "%s", aux);
    fprintf(pSalvar, "%c", ')');
    fprintf(pSalvar, "%s", salvar->pergunta);
    fprintf(pSalvar, "%c", '\n');

    free(aux);

    if(salvar->Sim != NULL)  salvarArvore(salvar->Sim, pSalvar);

    if(salvar->Nao != NULL)  salvarArvore(salvar->Nao, pSalvar);

}

/**@brief Funcao para carregar a arvore de um arquivo .txt para a memoria.
* A função recebe como parâmetro o ponteiro do arquivo em que a árvore se encontra,
*uma referência ao ponteiro que será utilizado para salvar a árvore em memória, bem como
*seu antecessor, para possibilitar a troca de direção dir -> esq ao fim da varredura,
*o primeiro índice lido em jogo20perguntas.c do arquivo, e a direção atual para controle
*de varredura.
* A função inicialmente aloca três campos auxiliares para captação dos dados contidos no arquivo,
*iniciando a varredura do arquivo na linha 93. Então, é colhido o índice inicial do arquivo, sendo
*armazenado em 'numero', realizando, após, a checagem do indice do ponteiro da memória com o contido
*no arquivo, para atribuição correta e respectiva dos nós e seus conteudos.
* Por fim, são desalocados os ponteiros auxilires e realizada uma checacgen de direção, invertendo
*ela caso ainda seja a inicial (1). A função returna o ponteiro raiz da arvore carregada.
*/
arvore *carregarArvore(FILE *pArquivo, arvore **salvar, arvore **pai, int indice, int direcao){

    int indiceArquivo;
    char *numero = (char*)malloc(4*(sizeof(char)));
    if(numero == NULL) printf("Falha ao alocar memória!! \n");
    char *pergunta = (char*)malloc(50*(sizeof(char)));
    if(pergunta == NULL) printf("Falha ao alocar memória!! \n");
    char *aux = (char*)malloc(2*(sizeof(char)));
    if(aux == NULL) printf("Falha ao alocar memória!! \n");


    rewind(pArquivo);        //Volta pro inicio do Arquivo p/ recursividade

    while(!feof(pArquivo)){

        fscanf(pArquivo, "%4[^)])", numero);
        //Conversao para inteiro para comparacao correta no if()
        indiceArquivo = atoi(numero);
        if(indiceArquivo == indice){     //Avalia se chegou na pergunta certa
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
      //Muda a direcao para a checagem no outro lado da arvore
        carregarArvore(pArquivo, &(*pai)->Nao, pai,((((*pai)->indice)*2) + 1) , 0);
    }

    return *pai;

}

/**@brief Função para percorrer a arvore.
*É checada a existência previa de nos, criando-os caso não
*existam.
* A função recebe como parâmetro a resposta dada pelo usuário ( 0 - Sim e 1 - Não ),
*utilizando de switch case para inserir novas perguntas (urilizando a função preencherNo),
*se não houver nós filhos, ou trocar a referência para o nó filho,
*returnando o nó atual em ambos os casos
*/
arvore *percorrer(int resp, arvore **raiz){

    char pergunta[50];

    switch (resp){                          //Checagem caso tenha carregado a arvore
        case 0: //SIM
            if((*raiz)->Sim == NULL){
                printf("Insira nova pergunta : ");
                fgets(pergunta, 50, stdin);
                strtok(pergunta, "\n");
    //Preenche o no seguinte baseado na resposta, com a pergunta inserida
                (*raiz)->Sim = preencherNo(pergunta, (((*raiz)->indice) * 2));
                return (*raiz)->Sim;
            }
            else
                return (*raiz)->Sim;

            break;

        case 1: //NÃO
            if((*raiz)->Nao == NULL){
                printf("Insira nova pergunta : ");
                fgets(pergunta, 50, stdin);
                strtok(pergunta, "\n");
                (*raiz)->Nao = preencherNo(pergunta, (1 + (2*(*raiz)->indice)));
                return (*raiz)->Nao;
            }
            else
                return (*raiz)->Nao;

            break;
        default:
            printf("Resposta inválida!\n");
            break;

    }
    return 0;

}

/**@brief Funcao para executar o jogo.
*Utilizando das funções anteriores, com laços
*de repetição e condições de parada relativas ao input do usuario.
* A função recebe como parâmetro uma referência ao ponteiro inicial da
*árvore, bem como o ponteiro do arquivo para poder salvar o jogo.
* Salvada a referência inicial em uma variável tipo arvore, a função
*realiza um loop (incrementando a quantidade de perguntas) imprimindo as
*perguntas da memória. Dependendo da resposta, a função toma a decisão adequada,
*como mais especificamente comentada no código. Por fim, é perguntado ao usuário se
*deseja salvar o jogo (arquivo .txt), abrindo o arquivo como "w+" e fechando logo após
*a chamada da função salvarArvore.
*/
void novoJogo(arvore **raiz, FILE *pSalvar){

    assert(*raiz!=NULL);
    assert(pSalvar!=NULL);
    int resp, respAux, indiceAux, quantidadePerguntas=0;
    arvore *salvar = *raiz;
    do{
        quantidadePerguntas++;               //Var. auxiliar para contagem de 20 perguntas
        printf("Pergunta : %s\n", (*raiz)->pergunta);
        printf("Resposta : \n0 - Sim \n1 - Nao\n7 - Acertou!!\n8 - Remover pergunta\n9 - Sair \n");
        scanf("%d", &resp);
        getchar();
        if(resp == 8){  //Remocao da pergunta
            indiceAux = (*raiz)->indice;
            removerNo(*raiz);
            printf("Pergunta removida com sucesso!\n");
            (*raiz) = (arvore*)malloc(sizeof(arvore));
            if((*raiz) == NULL) printf("Falha ao alocar memória!! \n");
            (*raiz)->Sim = NULL;
            (*raiz)->Nao = NULL;
            (*raiz)->indice = indiceAux;
            resp = 0;       //Decisao para supor a resposta "Sim" na nova pergunta inserida
        }
        else if(resp == 7){   //Acertou o que foi pensado pelo usuario
          printf("EBA ! GANHEI O JOGO :) \n");
          break;
        }
        (*raiz) = percorrer(resp, raiz);
    }while(resp != 9 && quantidadePerguntas < 20); //O loop acaba na primeira condicao falsa

    printf("O jogo acabou !!\n");
    printf("Deseja salvar o jogo?\n0 - Sim \n1 - Nao\n");
    scanf("%d",&resp);
    if(resp == 0){
       pSalvar = fopen("perguntas.txt", "w+"); //Abre no modo w+ para sobrescrever o arquivo com
       salvarArvore(salvar, pSalvar);          //o novo jogo
       fclose(pSalvar);
    }
}
