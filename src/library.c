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
        salvarArquivo(vetorClientes,vetorPoltronas);
    } else if (opcao == 3)
    {
        venderAcento(vetorClientes, vetorPoltronas);
        salvarArquivo(vetorClientes,vetorPoltronas);
    } else if (opcao == 4)
    {
        alterar(vetorClientes, vetorPoltronas);
        salvarArquivo(vetorClientes,vetorPoltronas);
    } else if (opcao == 5)
    {
        retirarPoltronaDaReserva(vetorClientes, vetorPoltronas);
        salvarArquivo(vetorClientes,vetorPoltronas);
    } else if (opcao == 6)
    {
        pesquisar(vetorClientes,vetorPoltronas);
    } else if (opcao == 7)
    {
        imprimir(vetorClientes,vetorPoltronas, 0);
    } else if (opcao == 8)
    {
        excluirCadastro(vetorClientes,vetorPoltronas);
        salvarArquivo(vetorClientes,vetorPoltronas);
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
    optCliente--;

    imprimir(vetorC, vetorP, 2);
    printf("Qual poltrona deseja reservar?");
    scanf("%d", &optPoltrona);
    optPoltrona--;

    vetorP[optPoltrona].status = 1;
    strcpy(vetorP[optPoltrona].cpfCliente, vetorC[optCliente].cpf);
    vetorC[optCliente].poltrona = optPoltrona;
}

void venderAcento( Cliente vetorC[], Poltrona vetorP[]){
    int optCliente, optPoltrona, i , j;
    imprimir(vetorC, vetorP, 1);    
    printf("Digite o número do cliente");
    scanf("%d", &optCliente);
    optCliente--;

    imprimir(vetorC, vetorP, 2);
    printf("Qual poltrona deseja reservar?");
    scanf("%d", &optPoltrona);
    optPoltrona--;

    vetorP[optPoltrona].status = 2;
    strcpy(vetorP[optPoltrona].cpfCliente, vetorC[optCliente].cpf);
    vetorC[optCliente].poltrona = optPoltrona; 
}

void alterar(Cliente vetorC[], Poltrona vetorP[]){
    char cpf[12];
    int optPoltrona;
    
    imprimir(vetorC,vetorP,1);
    printf("Digite o CPF do Cliente\n");
    scanf("%s", cpf);

    for(int i = 0; i < TAMC; i++){
        if(strcmp(vetorC[i].cpf, cpf) == 0){
            if(vetorC[i].poltrona >= 0){
                imprimir(vetorC,vetorP,2);
                if(vetorP[vetorC[i].poltrona].status == 1){
                    printf("\nO cliente: %s | poltrona: %d - RESERVADA", vetorC[i].nome, vetorC[i].poltrona); 
                    
                } else if(vetorP[vetorC[i].poltrona].status == 2){
                    printf("\nO cliente: %s | poltrona: %d - VENDIVA", vetorC[i].nome, vetorC[i].poltrona); 
                }
                printf("Digite o numero da poltrona que deseja alterar ou 0 para Cancelar: ");
                scanf("%d", &optPoltrona);
                optPoltrona--;
                vetorP[vetorC[i].poltrona].status = 0;
                vetorP[optPoltrona].status = 1;
                strcpy(vetorP[optPoltrona].cpfCliente, vetorC[i].cpf);
                strcpy(vetorP[vetorC[i].poltrona].cpfCliente, "");
                vetorC[i].poltrona = optPoltrona;
                printf("Poltrona alterada com sucesso!\n\n");
                return;
            }
            
        }
    }
    printf("O cliente não possui nenhuma reserva");
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

void pesquisar(Cliente vetorC[], Poltrona vetorP[]){
    int opt, cont;
    char cpf[12], nome[50], *aux;

    printf("\n\n1 - Pesquisar por nome\n2 - CPF\n\n");
    scanf("%d",&opt);

    switch(opt){
    case 1:
        imprimir(vetorC,vetorP,1);
        printf("\nDigite o nome do cliente ou 0 pra sair: ");
        scanf("%s",nome);

        printf("Clientes encontrados:\n");
        for(int i=0;i<TAMC;i++){
            aux = strstr(vetorC[i].nome,nome);
            if(aux != NULL && strcmp(aux,"") != 0){
                printf("\n%2d | %s %s\n", i + 1, vetorC[i].nome,vetorC[i].cpf);
                cont = 1;
            }  
        }
        if(cont != 1){
            printf("\nNenhum\n\n");
        }
        break;
    case 2:
        imprimir(vetorC,vetorP,1);
        do{
            printf("\nDigite o CPF do cliente ou 0 pra sair: ");
            scanf("%s",cpf);
            if(strlen(cpf) != 11){
                printf("\nDigite um CPF valido\n");
            }
            if(strcmp(cpf,"0") == 0){
                return;
            }
        }while(strlen(cpf) != 11);

        for(int i=0;i<TAMC;i++){
            if(strcmp(cpf,vetorC[i].cpf) == 0){
                printf("Cliente encontrado:\n%2d | %s %s\n", i + 1, vetorC[i].nome,vetorC[i].cpf);
                return; 
            }  
        }
        printf("\nCliente não encontrado\n\n");
        break;
    default:
        return;
    }
}

void imprimir(Cliente vetor[], Poltrona vetorP[], int opt){

    if(opt!=1 && opt!=2){
        printf("Imprimir:\n1 - Clientes\n2 - Poltronas\n");
        scanf("%d",&opt);
    }

    if (opt == 1)
    {
        for(int i = 0; i < TAMC; i++){
            if(strcmp(vetor[i].nome, "") != 0){
                printf("\n%2d | %s %s", i + 1, vetor[i].nome,vetor[i].cpf);  
            }
        }
        printf("\n\n");
    }
        
    else if(opt == 2){
        for(int i=0;i<TAMP;i++){
            if(vetorP[i].status == 0){
                printf("\n%2d",i+1);
            }else if(vetorP[i].status == 1){
                printf("\n%2d | AR | %s",i+1,vetorP[i].cpfCliente);
            }else if(vetorP[i].status == 2){
                printf("\n%2d | AV | %s",i+1,vetorP[i].cpfCliente);
            }
        }
        printf("\n\n");
    } else {
        printf("Opção invalida.\n");
    }
}

void excluirCadastro(Cliente vetorC[],Poltrona vetorP[]){
    int id,confirmacao;

    imprimir(vetorC,vetorP,1);

    printf("Digite o código do cliente que deseja excluir o cadastro ou 0 para sair:\n\n");
    scanf("%d",&id);

    printf("Digite 1 para confirmar exclusao: ");
    scanf("%d",&confirmacao);

    if(confirmacao != 1){
        printf("\nOperacao cancelada\n\n");
        return;
    }

    if(id!=0){
        id--;
        strcpy(vetorC[id].cpf,"");
        strcpy(vetorC[id].nome,"");
        vetorC[id].poltrona = -1;
        printf("\nCliente excluido com sucesso\n\n");
        return;
    }
    
    printf("\nOperacao cancelada\n\n");
    return;

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