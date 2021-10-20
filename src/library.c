#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/library.h"

void opcaoSelect(int opcao){
    //Opção direcionando para a função
    if (opcao == 1)
    {
        cadastrarCliente();
    } else if (opcao == 2)
    {
        reservarAcento();
    } else if (opcao == 3)
    {
        venderAcento();
    } else if (opcao == 4)
    {
        alterar();
    } else if (opcao == 5)
    {
        retirarPoltronaDaReserva();
    } else if (opcao == 6)
    {
        pesquisar();
    } else if (opcao == 7)
    {
        imprimir();
    } else if (opcao == 8)
    {
        excluirCadastro();
    } else if( opcao == 0){
        printf("Fim.");
    } else {
        printf("Opção inválida");
    }   
}

// Função para cadastrar clientes.
void cadastrarCliente(){
    FILE *listaClientes;
    //Abrindo arquivo
    listaClientes = fopen("clientes.txt", "a");

    struct Cliente cadastro;

    printf("Digite o nome: ");
    scanf("%s", cadastro.nome);
    // Se por ventura a pessoa não preencher o campo o sistema
    // o sistema continua solicitando para preencher o campo
    while (cadastro.nome == NULL){
        printf("Digite o nome: ");
        scanf("%s", cadastro.nome);
    if(cadastro.nome == NULL){
        printf("O campo nome precisa ser preenchido!");
        }
    }
    
    printf("Digite o CPF: ");
    scanf("%d", &cadastro.cpf);
    while (cadastro.cpf == ' '){
        printf("Digite o CPF: ");
        scanf("%d", &cadastro.cpf);
    if(cadastro.cpf == ' '){
        printf("O campo CPF precisa ser preenchido!");
        }  
    }

    //Salvando o cadastro
    fprintf(listaClientes, "%s\t%d\t%d\n", cadastro.nome, cadastro.cpf, -1);

    //Fechar aquivo
    fclose(listaClientes);
};

void reservarAcento(){

}

void venderAcento(){

}

void alterar(){

}

void retirarPoltronaDaReserva(){

}

void pesquisar(){

}

void imprimir(){

}

void excluirCadastro(){
    FILE *abrindoParaExcluir;
    char nome[50];
    char nomeNoArquivo;
    int cpfNoArquivo;
    int polt; 

    abrindoParaExcluir = fopen("clientes.txt", "r+");

    //Solicitando o nome do cadastro a ser excluido
    printf("Informe o nome do cliente a ser excluido");
    scanf("%s", nome);

    //Encontrando o arquivo para excluir
    while(fscanf(abrindoParaExcluir, "%s\t%d\t%d", nomeNoArquivo, &cpfNoArquivo, &polt) != EOF){
        if (strcmp(nomeNoArquivo, nome) == 0)
        {
            nomeNoArquivo = ' ';
            cpfNoArquivo = ' ';
            polt = ' ';
        }
    }

    fclose(abrindoParaExcluir);
}