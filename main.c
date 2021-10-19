#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdr/library.h"

int main(){
    int opcaoSelecionada;

    //Menu de opções
    do{
        printf("Menu:\n1) Cadastrar Cliente.\n2) Reservar acento.\n3) Vender acento.\n4) Alterar acento.\n5) Retirar poltrona da reserva.\n6) Pesquisar cliente.\n7) Imprimir.\n8) Excluir cadastro.\n0) Sair.\n");
        printf("Digite uma opcao:");
        scanf("%d", &opcaoSelecionada);
        opcaoSelect(opcaoSelecionada);
    } while (opcaoSelecionada != 0); 
 
}