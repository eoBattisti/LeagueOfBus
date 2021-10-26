#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/library.h"

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
        printf("\nMenu:\n"
        "1) Cadastrar Cliente.\n"
        "2) Reservar assento.\n"
        "3) Vender assento.\n"
        "4) Alterar assento.\n"
        "5) Retirar poltrona da reserva.\n"
        "6) Pesquisar cliente.\n"
        "7) Imprimir.\n"
        "8) Excluir cadastro.\n"
        "0) Sair.\n\n");
        printf("Digite uma opcao:");
        scanf("%d", &opcaoSelecionada);
        if(opcaoSelecionada >=0 || opcaoSelecionada<=9){
            opcaoSelect(opcaoSelecionada, arquivoClientes, arquivoOnibus, Clientes, 100);
        
        } else{
            printf("\n\nOpção invalida.\n\n");
        }
        
    } while (opcaoSelecionada != 0); 
 
}