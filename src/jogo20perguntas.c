/*
*  jogo20perguntas.c
*  Jogo 20 Perguntas
*
*  Created by Patrick Beal on 27/03/2018.
*  Copyright © 2018 Patrick Beal. All rights reserved.
*
*/

/**@brief Header para funcionamento completo do programa.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <headers.h>

/**@brief Main do jogo.
*
*A main realiza a filtragem inicial para a escolha do usuario.
*Baseada em input, ela decide por meio de switch case qual caminho
*seguir, executando as funcoes de 'funcoes.c' para execucao do jogo.
*/

int main(){

    FILE *pArquivo;
    int opcao =0;
    char *numero;

    pArquivo = fopen("perguntas.txt", "r+");

    arvore *raiz = (arvore *) malloc(sizeof(arvore));
    raiz->Sim = NULL;
    raiz->Nao = NULL;
    raiz->indice = 1;   //Primeiro nó é raiz
    arvore *salvar = NULL;

    printf(" *** Jogo das 20 Perguntas *** \n");
    printf("1) Iniciar novo jogo\n");
    printf("2) Carregar jogo\n");
    printf("3) Sair\n");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1: // Novo jogo
            printf("Digite sua pergunta inicial: \n");
            fgets(raiz->pergunta, 50, stdin);
            strtok(raiz->pergunta, "\n");    //Retira o '\n' inserido ao final da string
            fprintf(pArquivo, "%d", raiz->indice);
            fprintf(pArquivo, ")");
            fprintf(pArquivo, "%s", raiz->pergunta);
            novoJogo(&raiz,pArquivo);
            printf("\nFim de jogo!\n");
            break;
        case 2: //Carregar Jogo
            numero = malloc(4*(sizeof(char)));
            fscanf(pArquivo, "%4[^)])", numero);  //Le até o primeiro ')'
            fscanf(pArquivo, "%50[^\n]\n", raiz->pergunta); //Le até o primeiro '\n'
            raiz->Sim = NULL;
            raiz->Nao = NULL;
            raiz->indice = atoi(numero);
            free(numero);
            salvar = carregarArvore(pArquivo, &raiz->Sim, &raiz, 2, 1);
            printf("\nCarregando dados passados......\nFeito!\n");
            novoJogo(&salvar, pArquivo);
            printf("\nFim de jogo!\n");
            break;

        case 3:
            break;

        default:
            printf("Opção Inválida!!\n");
            removerNo(raiz);
            return 0;
    }

    removerNo(raiz);
    fclose(pArquivo);
    printf("Até a próxima!!!\n");
    return 0;

}
