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

arvore *percorrer(int resp, arvore **raiz){

    char pergunta[50];

    switch (resp){                          //Checagem caso tenha carregado a arvore
        case 0: //SIM
            if((*raiz)->Sim == NULL){
                printf("Insira nova pergunta : ");
                fgets(pergunta, 50, stdin);
                strtok(pergunta, "\n");
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

    }
    return 0;
}

void novoJogo(arvore **raiz, FILE *pSalvar){

    int resp, respAux, indiceAux, quantidadePerguntas=0;
    arvore *salvar = *raiz;
    do{
        quantidadePerguntas++;
        printf("Pergunta : %s\n", (*raiz)->pergunta);
        printf("Resposta : \n0 - Sim \n1 - Nao\n7 - Acertou!!\n8 - Remover pergunta\n9 - Sair \n");
        scanf("%d", &resp);
        getchar();
        if(resp == 8){
            indiceAux = (*raiz)->indice;
            removerNo(*raiz);
            printf("Pergunta removida com sucesso!\n");
            (*raiz) = (arvore*)malloc(sizeof(arvore));
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
