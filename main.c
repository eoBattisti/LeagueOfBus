#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdr/library.h"

int main(){
    int opcaoSelecionada;
    char arquivoClientes[50], arquivoOnibus[50];
    Cliente Clientes[100];

    printf("Defina o arquivo de clientes:");
    scanf("%s", arquivoClientes);

    printf("Defina o arquivo do onibus:");
    scanf("%s", arquivoOnibus);


    //Menu de opções
    do{
        printf("\nMenu:\n1) Cadastrar Cliente.\n2) Reservar acento.\n3) Vender acento.\n4) Alterar acento.\n5) Retirar poltrona da reserva.\n6) Pesquisar cliente.\n7) Imprimir.\n8) Excluir cadastro.\n0) Sair.\n");
        printf("Digite uma opcao:");
        scanf("%d", &opcaoSelecionada);
        opcaoSelect(opcaoSelecionada, arquivoClientes, arquivoOnibus, Clientes, 100);
    } while (opcaoSelecionada != 0); 
 
}