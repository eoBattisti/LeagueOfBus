#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../hdr/library.h"

//Recebe as opções que o usuário digitar na main  e chama as funções
void opcaoSelect(int opcao, Cliente vetorClientes[], Poltrona vetorPoltronas[]){
    //Opção direcionando para a função
    if (opcao == 1)
    {
        cadastrarCliente(vetorClientes);
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
        imprimir(vetorClientes,vetorPoltronas);
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
    if (arquivo)
    {
        fclose(arquivo);
        return 1;
    } 
    return 0;
}

//Independente se o arquivo é de clientes ou poltronas realiza o salvamento do arquivo
void salvarArquivo(Cliente vetorC[], Poltrona vetorP[]){
    FILE *arquivoP = fopen(ARQP, "w+b");
    FILE *arquivoC = fopen(ARQC, "w+b");
    fwrite(vetorP, sizeof(Poltrona), TAMP, arquivoP);
    fwrite(vetorC, sizeof(Cliente), TAMC, arquivoC);
    fclose(arquivoP);
    fclose(arquivoC);
}

//carrega um arquivo
void carregarArquivo(Cliente vetorC[], Poltrona vetorP[]){
    FILE *arquivoP = fopen(ARQP, "w+b");
    FILE *arquivoC = fopen(ARQC, "w+b");
    if(arquivoExiste(ARQC) && arquivoExiste(ARQP)){
        fread(vetorC, sizeof(Cliente), TAMC, arquivoC);
        fread(vetorP, sizeof(Poltrona), TAMP, arquivoP);
        fclose(arquivoC);
        fclose(arquivoP);
    }else{
        printf("\n\nERRO AO CARREGAR ARQUIVOS");
        exit(1);
    }
}

// Função para realizar o cadastro de clientes.
void cadastrarCliente(Cliente vetor[]){

    char nome[50];
    char cpf[12];
    int poltrona = -1;

    printf("Digite o nome: ");
    scanf("%s", nome);

    // continua solicitando o nome do cliente até ele ser preenchido
    while (strcmp(nome,"") == 0){
        printf("Digite o nome: ");
        scanf(" %[^\n]", nome);
        if(strcmp(nome,"") == 0){
             printf("O campo nome precisa ser preenchido!");
        }
    }

    printf("Digite o CPF: ");
    scanf("%s", cpf);

    // continua solicitando o cpf do cliente até ele ser preenchido
    while (strcmp(cpf,"") == 0){
        printf("\nDigite o CPF: ");
        scanf("%s", cpf);
        if(strcmp(cpf,"") == 0){
            printf("O campo CPF precisa ser preenchido!");
        }  
    }

    //Laço de verificação para encontrar a posição no vetor onde o nome estiver NULL
    // logo todos os outros campos serão 0, 0 respectivamente
    for(int i = 0; i < TAMC; i++){
        if(strcmp(vetor[i].nome, "") == 0) 
        {   
            //quando encontra a posição no vetor em branco adicona o cliente na posição
            strcpy(vetor[i].cpf,cpf);
            strcpy(vetor[i].nome, nome);
            vetor[i].poltrona = poltrona;
            printf("Cliente cadastrado com sucesso");
            break; //termina o laço após o cadastro
        }
    }
   
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

void imprimir(Cliente vetor[], Poltrona vetorP[]){
    int imprimirOq;
    char aux;


    printf("\nImprimir:\n1 - Cadastrados.\n2 - Onibus.\n");
    scanf("%d", &imprimirOq);

    if (imprimirOq == 1)
    {
        for(int i=0;i<TAMC;i++){
            printf("\nCliente %d: %s %s", i, vetor[i].nome, vetor[i].cpf);
        }
        
    }else if(imprimirOq == 2){
        for(int i=0;i<TAMP;i++){
            if(vetorP[i].status == 0){
                printf("\n%2d-LIVRE",i);
            }else if(vetorP[i].status == 1){
                printf("\n%2d-AR %s",i,vetorP[i].cpfCliente);
            }else if(vetorP[i].status == 2){
                printf("\n%2d-AV %s",i,vetorP[i].cpfCliente);
            }
        }
    } else {
        printf("Opção invalida.\n");
    }
}

void imprimirOnibus(Poltrona assentos[]){
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