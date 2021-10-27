#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../hdr/library.h"

//Recebe as opções que o usuário digitar na main  e chama as funções
void opcaoSelect(int opcao, Cliente vetorClientes[]){
    //Opção direcionando para a função
    if (opcao == 1)
    {
        cadastrarCliente();
    } else if (opcao == 2)
    {
        reservarAcento(vetorClientes);
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
    }else if (opcao == 7)
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

// Verifica se o arquivo existe
int arquivoExiste(char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo != NULL)
    {
        fclose(arquivo);
        return 1;
    } 
    exit(1);
}

// Função para realizar o cadastro de clientes.
void cadastrarCliente(){
    FILE *escrever = fopen("clientes.txt", "a");

    char nome[50];
    char cpf[11];
    int poltrona = -1;

    printf("Digite o nome: ");
    scanf(" %[^\n]", nome);
    // continua solicitando o nome do cliente até ele ser preenchido
    while (nome == NULL){
        printf("Digite o nome: ");
        scanf(" %[^\n]", nome);
        if(nome == NULL){
        printf("O campo nome precisa ser preenchido!\n");
        }
    }

    printf("Digite o CPF: ");
    scanf("%s", cpf);

    // continua solicitando o cpf do cliente até ele ser preenchido
    while (cpf == ' '){
        printf("Digite o CPF: ");
        scanf("%s", cpf);
    if(cpf == ' '){
        printf("O campo CPF precisa ser preenchido!\n");
        }  
    }

    fclose(escrever);    
};

//Funcao pra verificar se cliente existe?
int verificarCliente(char cpf[], char nome[]){
    FILE *cliente = fopen("clientes.txt", "r");
    //strcmp(v[].cpf,cpf);

}

void reservarAcento(){
    char cpf[11], nome[50];
    int op;

    printf("Informe o CPF do passageiro:\n");
    scanf("%s", cpf);
    printf("\nInforme o nome do passageiro:\n");
    scanf("%s", nome);
    
    
    if(verificarCliente(cpf,nome) == 0){
        printf("Cliente não cadastrado\n\nDeseja cadastrar? (S/N)");
        scanf("%d",&op);
        if(strcmp(toupper(op),"S")){
            cadastrarCliente();
        }
    } else{

    }
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
    FILE *cliente = fopen("clientes.txt", "r");
    int imprimirOq;
    char aux;

    printf("\nImprimir:\n1 - Cadastrados.\n2 - Onibus.\n");
    scanf("%d", &imprimirOq);
    printf("\nCadastro:\n");

    if (imprimirOq == 1)
    {
        while (fscanf(cliente, "%c", &aux) != EOF)
        {
            //cadastro
            printf("%c", aux);
        }
        
    } else {
        printf("Opção invalida.\n");
    }
    
    fclose(cliente);
}

/*void imprimirOnibus(Poltronas assentos[]){
    for(int i=0;i<40;i++){
        switch(assentos[i].status){
            case 0:
                printf("[%02d]",i);
                break;
            case 1:
                printf("[AR]");            
                break;
            case 2:
                printf("[AV]");
                break;
            default:
                printf("\n\n\nERRO NO PROGRAMA!\n\n");
                exit(1);
        }
        if( (i+1) % 10 == 0){
            printf("\n");
        }else if((i+1) % 20 == 0){
            printf("\n");
        }
    }
}*/

void criarOnibus(Poltronas assentos[]){
    for(int i=0;i<40;i++){
        assentos[i].cpfCliente = 0;
        assentos[i].status = 0;
    }
}

void excluirCadastro(){
}

