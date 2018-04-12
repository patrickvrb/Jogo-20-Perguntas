//
//  jogo20perguntas.c
//  Jogo 20 Perguntas
//
//  Created by Patrick Beal.
//  Copyright © 2018 Patrick Beal. All rights reserved.
//

#include <headers.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    FILE *pArquivo;

    int opcao =0;
    pArquivo = fopen("perguntas.txt", "r+");

    printf(" *** Jogo das 20 Perguntas *** \n");
    printf("1) Iniciar novo jogo\n");
    printf("2) Carregar jogo\n");
    printf("3) Sair\n");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1: // Novo jogo
            
            break;
        case 2: //Carregar Jogo
            break;

        case 3:
            break;

        default:
            printf("Opção Inválida!!\n");
            return 0;
    }

    fclose(pArquivo);
    printf("Até a próxima!!!\n");
    return 0;

}
