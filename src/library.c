#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../hdr/library.h"

//Recebe as opções que o usuário digitar na main  e chama as funções
void opcaoSelect(int opcao, char *nomeArquivoCliente, char *nomeArquivoOnibus, Cliente vetorClientes[], int tam){
    //Opção direcionando para a função
    if (opcao == 1)
    {
        cadastrarCliente(nomeArquivoCliente, vetorClientes, tam);
    } else if (opcao == 2)
    {
        reservarAcento(nomeArquivoCliente,vetorClientes,tam);
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
        imprimir(nomeArquivoCliente, vetorClientes, tam);
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

//Independente se o arquivo é de clientes ou poltronas realiza o salvamento do arquivo
void salvarArquivo(char *nomeArquivo, Cliente vetor[], int tam ){
    FILE *arquivo = fopen(nomeArquivo, "wb");
    fwrite(vetor, sizeof(Cliente), tam, arquivo);
    fclose(arquivo);
}

//carrega um arquivo
void carregarArquivo(char *nomeArquivo, Cliente vetor[], int tam){
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if(arquivoExiste(nomeArquivo)){
        fread(vetor, sizeof(Cliente), tam, arquivo);
        fclose(arquivo);
    } else{ 
        //Solicita ao usuário se o arquivo ainda não existir se deseja cria-lo
        fclose(arquivo); // fecha o arquivo para poder abrir em modo W
        char res;
        printf("Deseja criar o arquivo %s? (S/N):", nomeArquivo);
        scanf(" %c", &res);

        // recebe a resposta do usuário direciona pra criação ou não do arquivo
        if(toupper(res) == 'S'){
            arquivo = fopen(nomeArquivo, "wb");
            for(int i = 0; i < tam; i++){
                vetor[i].nome == NULL;
                vetor[i].cpf == 0;
                vetor[i].poltrona == 0;
            }
            fclose(arquivo);
        } else{
            printf("Error ao carregar o arquivo");
        }
    }
    
}

// Função para realizar o cadastro de clientes.
void cadastrarCliente(char *nomeArquivoCliente, Cliente vetor[], int tam){

    char nome[50];
    char cpf[11];
    int poltrona = -1;

    printf("Digite o nome: ");
    scanf("%s", nome);

    // continua solicitando o nome do cliente até ele ser preenchido
    while (nome == NULL){
        printf("Digite o nome: ");
        scanf(" %[^\n]", nome);
        if(nome == NULL){
        printf("O campo nome precisa ser preenchido!");
        }
    }

    printf("Digite o CPF: ");
    scanf("%s", cpf);

    // continua solicitando o cpf do cliente até ele ser preenchido
    while (cpf == ' '){
        printf("Digite o CPF: ");
        scanf("%s", cpf);
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
            strcpy(vetor[i].cpf,cpf);
            strcpy(vetor[i].nome, nome);
            vetor[i].poltrona = poltrona;
            printf("Cliente cadastrado com sucesso");
            break; //termina o laço após o cadastro
        }
    }

    //Salva as modificações do arquivo
    salvarArquivo(nomeArquivoCliente, vetor, tam);
    
};

void reservarAcento(char *nomeArquivoCliente, Cliente vetor[], int tam){
    char cpf[11];
    int op;

    printf("Informe o CPF do passageiro:\n");
    scanf("%s", cpf);
    
    if(verificarCliente(cpf,vetor,tam) == 0){
        printf("Cliente não cadastrado\n\nDeseja cadastrar? (S/N)");
        scanf("%d",&op);
        if(strcmp(op,toupper("s"))){
            cadastrarCliente(nomeArquivoCliente,vetor,tam);
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

void imprimir(char *nomeArquivoCliente, Cliente vetor[], int tam){
    FILE *cliente = fopen(nomeArquivoCliente, "r");
    int imprimirOq;
    char aux;


    printf("\nImprimir:\n1 - Cadastrados.\n2 - Onibus.\n");
    scanf("%d", &imprimirOq);

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

//Funcao pra verificar se cliente existe?
int verificarCliente(char cpf[], Cliente v[],int tam){

    for(int i=0;i<tam;i++){
        if(strcmp(v[i].cpf,cpf) == 0){
            return 1;
        }
    }
    return 0;
}