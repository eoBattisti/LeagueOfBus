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
        salvarArquivo(vetorClientes,vetorPoltronas);
    } else if (opcao == 2)
    {
        reservarAcento(vetorClientes,vetorPoltronas);
    } else if (opcao == 3)
    {
        venderAcento(vetorClientes, vetorPoltronas);
    } else if (opcao == 4)
    {
        alterar(vetorClientes, vetorPoltronas);
    } else if (opcao == 5)
    {
        retirarPoltronaDaReserva(vetorClientes, vetorPoltronas);
    } else if (opcao == 6)
    {
        pesquisar();
    } else if (opcao == 7)
    {
        imprimir(vetorClientes,vetorPoltronas, 1);
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
    printf("\n\nSALVO COM SUCESSO\n");
    fclose(arquivoP);
    fclose(arquivoC);
}

//carrega um arquivo
void carregarArquivo(Cliente vetorC[], Poltrona vetorP[]){
    FILE *arquivoP = fopen(ARQP, "rb");
    FILE *arquivoC = fopen(ARQC, "rb");
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

    do{
        printf("\nDigite o CPF: ");
        scanf("%s", cpf);
        if(strcmp(cpf,"") == 0){
            printf("O campo CPF precisa ser preenchido!");
        }   
    }while(strlen(cpf) != 11);

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

void reservarAcento( Cliente vetorC[], Poltrona vetorP[]){
    int optCliente, optPoltrona, i , j;
    imprimir(vetorC, vetorP, 1);    
    printf("Digite o número do cliente");
    scanf("%d", &optCliente);

    imprimir(vetorC, vetorP, 2);
    printf("Qual poltrona deseja reservar?");
    scanf("%d", &optPoltrona);
    vetorP[optPoltrona].status = 1;
    strcpy(vetorP[optPoltrona].cpfCliente, vetorC[optCliente].cpf);
    vetorC[optCliente].poltrona = optPoltrona;
}
void venderAcento( Cliente vetorC[], Poltrona vetorP[]){
    int optCliente, optPoltrona, i , j;
    imprimir(vetorC, vetorP, 1);    
    printf("Digite o número do cliente");
    scanf("%d", &optCliente);

    imprimir(vetorC, vetorP, 2);
    printf("Qual poltrona deseja reservar?");
    scanf("%d", &optPoltrona);
    vetorP[optPoltrona].status = 2;
    strcpy(vetorP[optPoltrona].cpfCliente, vetorC[optCliente].cpf);
    vetorC[optCliente].poltrona = optPoltrona; 
}

void alterar(Cliente vetorC[], Poltrona vetorP[]){
    char cpf[12];
    
    printf("Digite o CPF do Cliente");
    scanf("%s", cpf);

    for(int i = 0; i < TAMC; i++){
        if(strcmp(vetorC[i].cpf, cpf) == 0){
            if(vetorC[i].poltrona >= 0){
                if(vetorP[vetorC[i].poltrona].status == 1){
                    printf("O cliente: %s | poltrona: %d - RESERVADA", vetorC[i].nome, vetorC[i].poltrona); 
                    break;
                } else if(vetorP[vetorC[i].poltrona].status == 2){
                    printf("O cliente: %s | poltrona: %d - VENDIVA", vetorC[i].nome, vetorC[i].poltrona); 
                    break;
                }
            } else{
                printf("O cliente não possui nenhuma reserva");
            }
        }
    }

}

void retirarPoltronaDaReserva(Cliente vetorC[], Poltrona vetorP[]){
int optCliente, optPoltrona, i , j;
    imprimir(vetorC, vetorP, 1);    
    printf("Digite o número do cliente");
    scanf("%d", &optCliente);

    imprimir(vetorC, vetorP, 2);
    printf("Qual poltrona deseja retirar da reservar?");
    scanf("%d", &optPoltrona);
    vetorP[optPoltrona].status = 0;
    strcpy(vetorP[optPoltrona].cpfCliente, "");
    vetorC[optCliente].poltrona = -1;
}

void pesquisar(){

}

void imprimir(Cliente vetor[], Poltrona vetorP[], int opt){

    if (opt == 1)
    {
        for(int i = 0; i < TAMC; i++){
        if(strcmp(vetor[i].nome, "") != 0){
            printf("%2d | %s\n", i + 1, vetor[i].nome);  
            }
        }
    }
        
    else if(opt == 2){
        for(int i=0;i<TAMP;i++){
            if(vetorP[i].status == 0){
                printf("\n%2d",i);
            }else if(vetorP[i].status == 1){
                printf("\n%2d | AR | %s",i,vetorP[i].cpfCliente);
            }else if(vetorP[i].status == 2){
                printf("\n%2d | AV | %s",i,vetorP[i].cpfCliente);
            }
        }
    } else {
        printf("Opção invalida.\n");
    }
}

void excluirCadastro(){

}

void zerarVetores(Cliente Clientes[],Poltrona Poltronas[]){
    for(int i=0;i<TAMC;i++){
        strcpy(Clientes[i].nome,"");
        strcpy(Clientes[i].cpf,"");
        Clientes[i].poltrona=-1;
    }
    for(int i=0;i<TAMP-1;i++){
        strcmp(Poltronas[i].cpfCliente,NULL);
        Poltronas[i].status=0;
    }
}