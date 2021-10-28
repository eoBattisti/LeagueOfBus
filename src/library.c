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

//Verificando se o CPF tem 11 caracteres
int verificarCPF(char cpf[]){
    //contando a quantidade de digitos
    if(strlen(cpf) == 11){
        return 1;
    }
    return 0;
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
    char cpf[12];
    int poltrona = -1;

    strcpy(cpf,"");

    // continua solicitando o nome do cliente até ele ser preenchido
    do{
        printf("Digite o nome: ");
        scanf(" %[^\n]", nome);
        if(nome == NULL){
        printf("O campo 'nome' precisa ser preenchido!\n");
        }
    }while (nome == NULL);

    // continua solicitando o cpf do cliente até ele ser preenchido
    do{
        printf("Digite o CPF: ");
        scanf("%s", cpf);
        if(cpf == NULL){
            printf("O campo 'CPF' precisa ser preenchido!\n");
        }
    }while (cpf == NULL || verificarCPF(cpf) == 0);

    //escrever no arquivo
    fprintf(escrever, "%s\t%s\n", nome, cpf);

    //fechando o arquivo
    fclose(escrever);    
};

void reservarAcento(){
    char op;

    //verificando se o cadastro existe
    if(pesquisar() == 0){
        printf("Cliente não cadastrado\n\nDeseja cadastrar? (S/N)");
        scanf(" %c",&op);
        if(toupper(op) == 'S'){
            //solicitar cadastro caso não esteja cadastrado
            cadastrarCliente();
        }else{
            printf("\n\nReserva cancelada\n\n");
            return;
        }
    } 
    
}

void venderAcento(){

}

void alterar(){

}

void retirarPoltronaDaReserva(){

}

//Funcao pra verificar se cliente existe?
int pesquisar(){
    FILE *cliente = fopen("clientes.txt", "r");
    char encontrarCPF[12], encontrarNome[50];
    char cpf[11], nome[50];
    int opt;
    
    do{
        //solicitando como deseja pesquisar
        printf("\nPesquisar:\n1) Por Nome digite 1.\n2) Por CPF digite 2.\n0) Sair.\n");
        scanf("%d", &opt);

        if (opt == 1){
            //recebendo o nome
            printf("Informe o nome que deseja encontrar:\n");
            scanf("%s", encontrarNome);        
        } else if (opt == 2){
            //recebendo o cpf
            printf("Informe o CPF que deseja encotrar:\n");
            scanf("%s", encontrarCPF);
        } else if (opt == 0){
            return 0;
        }
    }while (opt < 0 || opt > 2);

    while (fscanf(cliente, "%[^\t] %[^\n] ", nome, cpf) != EOF){
        if (strcmp(encontrarNome, nome) == 0 && opt == 1){
            printf("Conta encontrada: %s %s\n\n", encontrarCPF, encontrarNome);
            return 1;
        } else if (strcmp(encontrarCPF, cpf) == 0 && opt == 2){
            printf("Conta encontrada: %s %s\n\n", encontrarCPF, encontrarNome);
            fclose(cliente);
            return 1;
        } 
    }
    printf("Conta não encontrada.\n"); 
    fclose(cliente);
    return 0;
}

void imprimir(){
    FILE *cliente = fopen("clientes.txt", "r");
    FILE *onibus = fopen("poltronas.txt", "r");
    int imprimirOq;
    char aux;

    //dando a opção de arquivos
    do{
    printf("\nImprimir:\n1 - Cadastrados.\n2 - Onibus.\n0 - Sair.\n");
    scanf("%d", &imprimirOq);
    printf("\nCadastro:\n");
    } while (imprimirOq > 2 || imprimirOq < -1);
    

    if (imprimirOq == 1)
    {
        while (fscanf(cliente, "%c", &aux) != EOF)
        {
            //Imprimindo cadastro
            printf("%c", aux);
        }
        
    }else if(imprimirOq == 2){
        while (fscanf(onibus, "%c", &aux) != EOF)
        {
            //Imprimindo onibus
            printf("%c", aux);
        }
    }else if(imprimirOq == 2){
        
    } else {
        printf("Opção invalida.\n");
    }
    
    //Fechando arquivo
    fclose(cliente);
    fclose(onibus);
}

void criarOnibus(Poltronas assentos[]){
    //função criar arquivo txt
    
}

void excluirCadastro(){
}

