#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hdr/library.h"

void opcaoSelect(int opcao, char *nomeArquivoCliente, char *nomeArquivoOnibus, Cliente vetorClientes[], int tam){
    //Opção direcionando para a função
    if (opcao == 1)
    {
        cadastrarCliente(nomeArquivoCliente, vetorClientes, tam);
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

void salvarArquivo(char *nomeArquivo, Cliente vetor[], int tam ){
    FILE *arquivo = fopen(nomeArquivo, "wb");
    fread(vetor, sizeof(Cliente), tam, arquivo);
    fclose(arquivo);
}

void carregarArquivo(char *nomeArquivo, Cliente vetor[], int tam){
    FILE *arquivo = fopen(nomeArquivo, "rb");
    fread(vetor, sizeof(Cliente), tam, arquivo);
    fclose(arquivo);
}

// Função para realizar o cadastro de clientes.
void cadastrarCliente(char *nomeArquivoCliente, Cliente vetor[], int tam){

    char nome[50];
    int cpf;
    int poltrona = -1;

    printf("Digite o nome: ");
    scanf("%s", nome);

    // continua solicitando o nome do cliente até ele ser preenchido
    while (nome == NULL){
        printf("Digite o nome: ");
        scanf("%s", nome);
        if(nome == NULL){
        printf("O campo nome precisa ser preenchido!");
        }
    }

    printf("Digite o CPF: ");
    scanf("%s", &cpf);

    // continua solicitando o cpf do cliente até ele ser preenchido
    while (cpf == ' '){
        printf("Digite o CPF: ");
        scanf("%d", &cpf);
    if(cpf == ' '){
        printf("O campo CPF precisa ser preenchido!");
        }  
    }

    //Laço de verificação para encontrar a posição no vetor onde o nome estiver NULL
    // logo todos os outros campos serão 0, 0 respectivamente
    for(int i = 0; i < tam; i++){
        if((vetor[i].nome == NULL)) 
        {   
            //quando encontra a posição no vetor em branco adicona o cliente na posição
            vetor[i].cpf = cpf;
            strcpy(vetor[i].nome, nome);
            vetor[i].poltrona = poltrona;
            printf("Cliente cadastrado com sucesso");
            break; //termina o laço após o cadastro
        }
    }

    //Salva as modificações do arquivo
    salvarArquivo(nomeArquivoCliente, vetor, tam);
    
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

void imprimirOnibus(Poltronas assentos[]){
    for(int i=0;i<40;i++){
        switch(assentos[i].status){
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            default:
                break;
        }
    }
}

void excluirCadastro(){
}


