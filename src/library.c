#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../hdr/library.h"

//Recebe as opções que o usuário digitar na main  e chama as funções
void opcaoSelect(int opcao, Cliente *vetor){
    //Opção direcionando para a função
    if (opcao == 1){
        //feito
        cadastrarCliente(vetor);
    } else if (opcao == 2)
    {
        reservarAcento(vetor);
    } else if (opcao == 3)
    {
        venderAcento();
    } else if (opcao == 4)
    {
        alterar();
    } else if (opcao == 5)
    {
        retirarPoltronaDaReserva();
    } else if (opcao == 6){
        //falta pesquisar por nome
        pesquisar();
    }else if (opcao == 7){
        //feito
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
void cadastrarCliente(Cliente *vetor){
    FILE *escrever = fopen("clientes.bin", "ab");

    // continua solicitando o nome do cliente até ele ser preenchido
    do{
        printf("Digite o nome: ");
        scanf(" %[^\n]", vetor->nome);
        if(vetor->nome == NULL){
        printf("O campo 'nome' precisa ser preenchido!\n");
        }
    }while (vetor->nome == NULL);

    // continua solicitando o cpf do cliente até ele ser preenchido
    do{
        printf("Digite o CPF: ");
        scanf("%s", vetor->cpf);
        if(vetor->cpf == NULL){
            printf("O campo 'CPF' precisa ser preenchido!\n");
        }
    }while (vetor->cpf == NULL || verificarCPF(vetor->cpf) == 0);

    //escrever no arquivo
    fwrite(&vetor, sizeof(Cliente), 1, escrever);

    //fechando o arquivo
    fclose(escrever);    
};

void reservarAcento(Cliente *vetor){
    int cont = 0;
    char op;
    char nPoltrona[3], nCadastro[12], reservaAssento[3], reservaCPF[12];

    //verificando se o cadastro existe
    if(pesquisar() == 0){
        printf("Cliente não cadastrado\n\nDeseja cadastrar? (S/N)");
        scanf(" %c",&op);
        if(toupper(op) == 'S'){
            //solicitar cadastro caso não esteja cadastrado
            cadastrarCliente(vetor);
        }else{
            printf("\n\nReserva cancelada\n\n");
            
        }
    } 
    
    FILE *poltrona = fopen("poltronas.txt","r+");
    FILE *cliente = fopen("clientes.txt","r");

    printf("\n\nInsira poltrona deseja reservar: ");
    scanf(" %s", reservaAssento);

    /*if(reservaAssento >= 48 && reservaAssento <= 57){
        reservaAssento[2] = reservaAssento[1];
        reservaAssento[1] = reservaAssento[0];
        reservaAssento[0] = '0';
    }*/
    
    do{
        printf("\n\nInsira seu CPF: ");
        scanf("%s", reservaCPF);
    }while(strlen(reservaCPF) != 11);

    while(fscanf(poltrona,"%[^\t] %[^\n] ",nPoltrona,nCadastro) != EOF){
        if(strcmp(nPoltrona,reservaAssento)==0){
            break;
        }
        cont++;
    }

    printf("CONT = %d\n\n", cont);

    rewind(poltrona);

    while(fscanf(poltrona,"%[^\t] %[^\n] ",nPoltrona,nCadastro) != EOF){
        cont--;
            printf("%s\t%s\t%d\t%s\n",nPoltrona,nCadastro,cont,reservaCPF);
        if(cont == 0){
            fprintf(poltrona,"AR\t%s\n",reservaCPF);
            break;
        }
    }

    fclose(poltrona);
    fclose(cliente);

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
    char cpf[12], nome[50];
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
    }while (opt < -1 || opt > 2);

    while (fscanf(cliente, "%[^\t] %[^\n] ", nome, cpf) != EOF){   
        if (strcmp(encontrarNome, nome) == 0 && opt == 1){
            printf("Conta encontrada: %s %s\n\n", nome, cpf);
            return 1;
        } else if (strcmp(encontrarCPF, cpf) == 0 && opt == 2){
            printf("Conta encontrada: %s %s\n\n", nome, cpf);
            fclose(cliente);
            return 1;
        } 
    }
    printf("Conta não encontrada.\n"); 
    fclose(cliente);
    return 0;
}

void imprimir(){
    FILE *cliente = fopen("clientes.bin", "rb");
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
    }else if(imprimirOq == 0){
        
    }
    
    //Fechando arquivo
    fclose(cliente);
    fclose(onibus);
}

void criarOnibus(){
    //função criar arquivo txt
    FILE *poltronas = fopen("poltronas.txt","w+");
    for(int i=1;i<=40;i++){
        fprintf(poltronas,"%02d\t00000000000\n",i);
    }
    fclose(poltronas);
}

void excluirCadastro(){
    FILE *cliente = fopen("clientes.txt", "r+");
    char encontrarNome[50];
    char encontrarCPF[12];
    char nome[50], cpf[12];
    int confirma;

    printf("Informe o CPF que deseja escluir:\n");
    scanf("%s", encontrarCPF);

    while (fscanf(cliente, "%[^\t] %[^\n] ", nome, cpf) != EOF){
        if (strcmp(encontrarCPF, cpf) == 0){
            printf("Conta encontrada: %s %s\n\n", encontrarCPF, encontrarNome);
            printf("Deseja mesmo excluir o contato? se sim digite '1'");
            scanf("%d", &confirma);
            if (confirma == 1){
                //falta fazer
            }
            
        }
    }
    
}

