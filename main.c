#include <stdio.h>
#include <stdlib.h>

struct Cliente{
    //Campos a ser preenchidos
    char nome[25];
    int cpf;
};

struct Cliente cadastrarCliente();



int main(){
    FILE *listaClientes;
    struct Cliente cliente;    

    listaClientes = fopen("clientes.txt", "a");

    cliente = cadastrarCliente();
    
    fprintf(listaClientes, "%s\t%d\n", cliente.nome, cliente.cpf);
    
    fclose(listaClientes);
}

// Função para cadastrar clientes.
struct Cliente cadastrarCliente()
{
    struct Cliente cadastro;

    printf("Digite o nome: ");
    scanf("%s", cadastro.nome);
    // Se por ventura a pessoa não preencher o campo o sistema
    // o sistema continua solicitando para preencher o campo
    if(cadastro.nome == NULL){
        printf("O campo nome precisa ser preenchido!");
        while (cadastro.nome == NULL)
        {
        printf("Digite o nome: ");
        scanf("%s", cadastro.nome);
        }
    }
    
    printf("Digite o CPF: ");
    scanf("%d", &cadastro.cpf);
     if(cadastro.cpf == NULL){
        printf("O campo CPF precisa ser preenchido!");
        while (cadastro.cpf == NULL)
        {
            printf("Digite o CPF: ");
            scanf("%d", &cadastro.cpf);
        }
    }

    //retorna a struct Cliente
    return cadastro;
};
