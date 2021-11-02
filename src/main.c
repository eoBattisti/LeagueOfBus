#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/library.h"


int main(){
    int opcaoSelecionada;
    char sex;
    Cliente Clientes[TAMC];
    Poltrona Poltronas[TAMP];
    
    // zerarVetores(Clientes,Poltronas);
    // printf("\nClientes:\n");
    // for(int i=0;i<TAMC;i++){
    //     printf("%s\n", Clientes[i].nome);
    // }

    // printf("\nPoltronas:\n");
    // for(int i=0;i<TAMP;i++){
    //     printf("%d\n", Poltronas[i].status);
    // }

    carregarArquivo(Clientes,Poltronas);

    //Menu de opções
    do{
        printf("\n\n\nMenu:\n"
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
            opcaoSelect(opcaoSelecionada, Clientes, Poltronas);
        
        } else{
            printf("\n\nOpção invalida.\n\n");
        }
        
    } while (opcaoSelecionada != 0); 
 
}