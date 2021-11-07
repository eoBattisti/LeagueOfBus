#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../hdr/library.h"
#include <locale.h>
#include <conio.h>

//Recebe as opções que o usuário digitar na main  e chama as funções
void opcaoSelect(int opcao, Cliente vetorClientes[], Poltrona vetorPoltronas[]){
    //Opção direcionando para a função
     if (opcao == 1) // Cadastrar cliente
    {
        cadastrarCliente(vetorClientes);
        salvarArquivo(vetorClientes,vetorPoltronas);
    } else if (opcao == 2) // Reservar assento
    {
        reservarAssento(vetorClientes,vetorPoltronas);
        salvarArquivo(vetorClientes,vetorPoltronas);
    } else if (opcao == 3) // Vender assento
    {
        venderAssento(vetorClientes, vetorPoltronas);
        salvarArquivo(vetorClientes,vetorPoltronas);
    } else if (opcao == 4) // Alterar assento
    {
        alterar(vetorClientes, vetorPoltronas);
        salvarArquivo(vetorClientes,vetorPoltronas);
    } else if (opcao == 5) // Retirar assento da reserva
    {
        retirarPoltronaDaReserva(vetorClientes, vetorPoltronas);
        wait();
        salvarArquivo(vetorClientes,vetorPoltronas);
    } else if (opcao == 6) // Pesquisar cliente
    {
        pesquisar(vetorClientes,vetorPoltronas);
        wait();
    } else if (opcao == 7) // Imprimir
    {
        imprimir(vetorClientes,vetorPoltronas, 0);
        wait();
    } else if (opcao == 8) // Excluir cadastro
    {
        excluirCadastro(vetorClientes,vetorPoltronas);
        salvarArquivo(vetorClientes,vetorPoltronas);
    } else if( opcao == 0){ // Sair
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
    successMessage("\n\nArquivo salvo com sucesso\n");
    fclose(arquivoP);
    fclose(arquivoC);
}

//carrega um arquivo
void carregarArquivo(Cliente vetorC[], Poltrona vetorP[]){
    FILE *arquivoP = fopen(ARQP, "rb");
    FILE *arquivoC = fopen(ARQC, "rb");
    //verifica se os arquivos existem
    if(arquivoExiste(ARQC) && arquivoExiste(ARQP)){
        fread(vetorC, sizeof(Cliente), TAMC, arquivoC);
        fread(vetorP, sizeof(Poltrona), TAMP, arquivoP);
        fclose(arquivoC);
        fclose(arquivoP);
    }else{
        errorMessage("\n\nErro ao carregar os arquivos");
        exit(1);
    }
}

// Função para realizar o cadastro de clientes.
void cadastrarCliente(Cliente vetor[]){
    
    char nome[50];
    char cpf[12];
    int poltrona = -1, aux = 0;

    // continua solicitando o nome do cliente até ele ser preenchido
    do{
        printf("Digite o nome: ");
        scanf(" %50[ .a-zA-Z]%*[^\n]\n", nome);
        if(strcmp(nome,"") == 0){
             warningMessage("O campo nome precisa ser preenchido!");
        }
    }while (strcmp(nome,"") == 0);

    do{
        printf("\nDigite o CPF: ");
        scanf("%s", cpf);
        if(strcmp(cpf,"") == 0){
            warningMessage("O campo CPF precisa ser preenchido!");
        }   
        for(int i=0;i<TAMC;i++){
            aux = 0;
            if(strcmp(cpf,vetor[i].cpf) == 0){
                warningMessage("\nCliente já cadastrado");
                aux = 1;
                break;
            }
        }
    }while(strlen(cpf) != 11 && aux == 1);

    //Laço de verificação para encontrar a posição no vetor onde o nome estiver NULL
    // logo todos os outros campos serão 0, 0 respectivamente
    for(int i = 0; i < TAMC; i++){
        
        if(strcmp(vetor[i].nome, "") == 0) 
        {   
            //quando encontra a posição no vetor em branco adicona o cliente na posição
            strcpy(vetor[i].cpf, cpf);
            strcpy(vetor[i].nome, nome);
            vetor[i].poltrona = poltrona;
            successMessage("Cliente cadastrado com sucesso");
            break; //termina o laço após o cadastro
        }
    }
   
};

// Reserva o Assento
void reservarAssento( Cliente vetorC[], Poltrona vetorP[]){
    int optCliente, optPoltrona, i , j, cont;

    // Verifica se há assentos disponíveis
    for(int i=0;i<TAMP;i++){
        if(vetorP[TAMP-1].status == 1 || vetorP[TAMP-1].status == 2){
            cont++;
        }
    }

    if(cont == 40){
        warningMessage("Não ha mais assentos vagos no onibus.\n\n");
    }

    //imprime o vetor de clientes para que o usuário selecione o cliente
    imprimir(vetorC, vetorP, 1);    
    printf("Digite o número do cliente: ");
    scanf("%d", &optCliente);
    optCliente--;

    //Impime o vetor das poltranas para que o usuário selecione a poltrona
    imprimir(vetorC, vetorP, 2);
    printf("Digite a poltrona que deseja reservar: ");
    scanf("%d", &optPoltrona);
    optPoltrona--;

    if(vetorP[optPoltrona].status == 1 || vetorP[optPoltrona].status == 2){
        warningMessage("\nEsta poltrona já está reservada ou vendida");
        return;
    }
        

    //Muda o status da poltrona para reservarda
    vetorP[optPoltrona].status = 1;
    
    //Copia o cpf do cliente para a poltona selecionada
    strcpy(vetorP[optPoltrona].cpfCliente, vetorC[optCliente].cpf);
    
    //O cliente na atributo poltrona recebe o número da poltrona selecionada
    vetorC[optCliente].poltrona = optPoltrona;

    successMessage("\nReserva realizada com sucesso!\n");
}

// Realiza a venda dos assentos
void venderAssento( Cliente vetorC[], Poltrona vetorP[]){
    int optCliente, optPoltrona, i , j, cont;

     // Verifica se há assentos disponíveis
    

    for(int i=0;i<TAMP;i++){
        if(vetorP[TAMP-1].status == 1){
            cont++;
        }
    }

    if(cont == 40){
        warningMessage("Não ha mais assentos vagos no onibus.\n\n");
    }

    //imprime o vetor de clientes para que o usuário selecione o cliente
    imprimir(vetorC, vetorP, 1);    
    printf("Digite o número do cliente: ");
    scanf("%d", &optCliente);
    optCliente--;

    //Impime o vetor das poltranas para que o usuário selecione a poltrona
    imprimir(vetorC, vetorP, 2);
    printf("Digite a poltrona que deseja comprar: ");
    scanf("%d", &optPoltrona);
    optPoltrona--;

    // Verifica se a poltrona já está vendida
    if(vetorP[optPoltrona].status == 2){
        warningMessage("\nEsta poltrona já está vendida");
        return;
    }

    // Verifica se a poltrona já está reservada 
    if(vetorP[optPoltrona].status == 1){
        // Verifica se cpf do cliente é o mesmo que o da poltrona reservada
        // Se não, não permite realizar a venda
        if(strcmp(vetorP[optPoltrona].cpfCliente, vetorC[optCliente].cpf) != 0){
            warningMessage("Poltrona ja esta reservada para outro cliente");
            return;
        }
    }
      

    //Muda o status da poltrona para Vendida 
    vetorP[optPoltrona].status = 2;

    //Copia o cpf do cliente para a poltona selecionada
    strcpy(vetorP[optPoltrona].cpfCliente, vetorC[optCliente].cpf);

    //O cliente na atributo poltrona recebe o número da poltrona selecionada
    vetorC[optCliente].poltrona = optPoltrona; 

    successMessage("\nVenda realizada com sucesso!\n");
}

// Altera o status de uma poltrona para outra
void alterar(Cliente vetorC[], Poltrona vetorP[]){
    
    int optPoltrona, optCliente;
    
    // solicita o CPF do cliente 
    imprimir(vetorC,vetorP,1);
    printf("Digite o número do Cliente\n");
    scanf("%d", &optCliente);
    optCliente--;

    if(vetorP[vetorC[optCliente].poltrona].status == 1){
        //informa o qual poltrona o cliente já possui
        printf("\n\nCliente: %s | poltrona: %d - RESERVADA", vetorC[optCliente].nome, vetorC[optCliente].poltrona+1); 
        imprimir(vetorC, vetorP, 2);
        printf("Digite o numero da poltrona que deseja alterar ou 0 para Cancelar: ");
        scanf("%d", &optPoltrona);
        optPoltrona--;

        // se o usuário digitar o número de uma poltrona já ocupada não permite que 
        // a reserva seja efetuada
        if(vetorP[optPoltrona].status != 0){
            printf("A poltrona %d não pode ser reservada", optPoltrona + 1);
            return;
        }
        
        // zera o status da poltrona anterior
        vetorP[vetorC[optCliente].poltrona].status = 0;

        // altera o status para reservada na poltrona selecionada
        vetorP[optPoltrona].status = 1;

        // copia o cpf do cliente para nova poltrona
        strcpy(vetorP[optPoltrona].cpfCliente, vetorC[optCliente].cpf);
        
        // zera o cpf do cliente na poltrona anterior
        strcpy(vetorP[vetorC[optCliente].poltrona].cpfCliente, "");
        
        // Coloca o número da nova no atributo poltrona do cliente
        vetorC[optCliente].poltrona = optPoltrona;

        successMessage("Alteração feita com sucesso");

        return;

    } else if(vetorP[vetorC[optCliente].poltrona].status == 2){
        printf("\n\nCliente: %s | poltrona: %d - VENDIDA", vetorC[optCliente].nome, vetorC[optCliente].poltrona+1);
        imprimir(vetorC, vetorP, 2);
        printf("Digite o numero da poltrona que deseja alterar ou 0 para Cancelar: ");
        scanf("%d", &optPoltrona);
        optPoltrona--;

        // se o usuário digitar o número de uma poltrona já ocupada não permite que 
        // a reserva seja efetuada
        if(vetorP[optPoltrona].status != 0){
            printf("A poltrona %d não pode ser ", optPoltrona + 1);
            return;
        }

        // zera o status da poltrona anterior
        vetorP[vetorC[optCliente].poltrona].status = 0;

        // altera o status para reservada na poltrona selecionada
        vetorP[optPoltrona].status = 2;

        // copia o cpf do cliente para nova poltrona
        strcpy(vetorP[optPoltrona].cpfCliente, vetorC[optCliente].cpf);


        // zera o cpf do cliente na poltrona anterior
        strcpy(vetorP[vetorC[optCliente].poltrona].cpfCliente, "");

        // Coloca o número da nova no atributo poltrona do cliente
        vetorC[optCliente].poltrona = optPoltrona; 

        successMessage("\n\nAlteração feita com sucesso");
        return;
    }
    warningMessage("\n\nO cliente não possui nenhuma reserva");
}

// Opção de retirar a poltrona de um cliente
void retirarPoltronaDaReserva(Cliente vetorC[], Poltrona vetorP[]){
    int optCliente, optPoltrona, i , j;
    imprimir(vetorC, vetorP, 1);    
    printf("Digite o número do cliente: ");
    scanf("%d", &optCliente);
    optCliente--;
    printf("\n\n");

    imprimir(vetorC, vetorP, 2);
    printf("Digite a poltrona que deseja retirar da reserva: ");
    scanf("%d", &optPoltrona);
    optPoltrona--;

    if(vetorP[optPoltrona].status == 1 || vetorP[optPoltrona].status == 2){
        if(strcmp(vetorP[optPoltrona].cpfCliente,vetorC[optCliente].cpf)==0){
            vetorP[optPoltrona].status = 0;
            strcpy(vetorP[optPoltrona].cpfCliente, "");
            vetorC[optCliente].poltrona = -1;
            successMessage("\n\nPoltrona retirada da reserva\n");
            return;
        }
        warningMessage("\n\nO Cliente não possui reserva nesta poltrona\n");
        return;
    }
    warningMessage("\n\nNão há reserva nesta poltrona\n");
}


// Opção de pesquisar um cliente cadastrado por nome ou cpf
void pesquisar(Cliente vetorC[], Poltrona vetorP[]){
    int opt, cont, cadastrado = 0;
    char cpf[12], nome[50], *aux, auxNome[50];

    // Verifica se há clientes cadastrados
    for(int i=0;i<TAMC;i++){
        if(vetorC[i].poltrona == -1){
            cadastrado = 0;
            break;
        }
        cadastrado = 1;
    }
    //
    if(cadastrado == 1){
        warningMessage("\n\nNão ha clientes cadastrados\n");
        return;
    }

    do{ // Usuário informa o que deseja pesquisar
        printf("\n\n1 - Pesquisar por nome\n2 - CPF\n0 - Sair\n\n");
        scanf("%d",&opt);
    }while(opt < 0 || opt > 2);

    switch(opt){
    case 1: 
        // Pesquisa por nome
        imprimir(vetorC,vetorP,1);
        printf("\nDigite o nome do cliente ou 0 pra sair: ");
        scanf("%s",nome);
        
        // Transforma todas as letras em minusculas
        for(int k = 0; k < strlen(nome); k++){
            nome[k] = tolower(nome[k]);
        }
        
        printf("Clientes encontrados:\n");
        

        for(int i=0;i<TAMC;i++){
            // Transforma todas as letras dos nomes do vetor em minusculas
            for(int j = 0; j < strlen(vetorC[i].nome); j++){
               auxNome[j] = tolower(vetorC[i].nome[j]);
            }

            // Compara se há aquele nome
            aux = strstr(auxNome ,nome);
            if((aux != NULL) && (strcmp(aux,"") != 0)){
                printf("%2d | %s %s\n", i + 1, vetorC[i].nome,vetorC[i].cpf);
                cont = 1;
            }  

            strcpy(auxNome, "");
        }
        
        if(cont != 1){
            printf("\nNenhum\n\n");
        }
        
        break;
    case 2: // Pesquisa por CPF
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
                printf("%2d | %s %s\n", i + 1, vetorC[i].nome,vetorC[i].cpf);
                return; 
            }  
        }
        warningMessage("\nCliente não encontrado\n\n");
        break;
    default: // Erro
        return;
    }
}

// Imprime os clientes ou as poltronas ao usuário
void imprimir(Cliente vetor[], Poltrona vetorP[], int opt){

    if(opt!=1 && opt!=2){ // Variável informada no parâmetro
        printf("Imprimir:\n1 - Clientes\n2 - Poltronas\n");
        scanf("%d",&opt);
    }

    if (opt == 1){ // Imprime os clientes
        for(int i = 0; i < TAMC; i++){
            if(strcmp(vetor[i].nome, "") != 0){
                printf("\n%2d | %s %s", i + 1, vetor[i].nome,vetor[i].cpf);  
            }
            
        }
        printf("\n\n");

    }
        
    else if(opt == 2){ // Imprime as poltronas do ônibus
        for(int i=0;i<TAMP;i++){
            if(vetorP[i].status == 0){
                printf("%2d \t",i+1);
            }else if(vetorP[i].status == 1){
                printf("%2d | AR | %s \t",i+1,vetorP[i].cpfCliente);
            }else if(vetorP[i].status == 2){
                printf("%2d | AV | %s \t",i+1,vetorP[i].cpfCliente);
            }

            if(i % 4 == 3){
                printf("\n");
            }
        }
        printf("\n\n");
    } 
    
    else {
        warningMessage("Opção invalida.\n");
    }
}

// Opção de excluir o cadastro de algum cliente
void excluirCadastro(Cliente vetorC[],Poltrona vetorP[]){
    int id,confirmacao, cadastro = 0;

    // Verifica se há clientes cadastrados
    for(int i=0;i<TAMC;i++){
        if(strcmp(vetorC[i].cpf,"") != 0){
            cadastro = 1;
            break;
        }
    }
    if(cadastro == 0){
        warningMessage("\n\nNão há clientes cadastrados\n");
        wait();
        return;
    }

    imprimir(vetorC,vetorP,1); // Imprime os clientes para facilitar ao usuário

    printf("Digite o código do cliente que deseja excluir o cadastro ou 0 para sair:\n\n");
    scanf("%d",&id);
    id--;

    // Verifica se cliente existe
    if(strcmp(vetorC[id].cpf,"") == 0 && strcmp(vetorC[id].nome,"") == 0){
        warningMessage("\nCliente nao existe\n");
        return;
    }

    // Confirmação de exclusão
    warningMessage("\nDigite 1 para confirmar exclusao: ");
    scanf("%d",&confirmacao);

    if(confirmacao != 1){
        warningMessage("\nOperacao cancelada\n\n");
        return;
    }

    // Exclui todos os campos do cliente
    if(id>-1){
        // Substitui as posições do vetor para as subsequentes
        for(int i=id;i<TAMC-1;i++){
            strcpy(vetorC[i].cpf,vetorC[i+1].cpf);
            strcpy(vetorC[i].nome,vetorC[i+1].nome);
            vetorC[i].poltrona = vetorC[i+1].poltrona;
        }
        
        strcpy(vetorC[TAMC-1].cpf,"");
        strcpy(vetorC[TAMC-1].nome,"");
        vetorC[TAMC-1].poltrona = -1;

        successMessage("\nCliente excluido com sucesso\n\n");
        return;
    }
    
    warningMessage("\nOperacao cancelada\n\n");
    return;

}


// Zera os vetores e reseta os dados do sistema
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

// Função para espera 
void wait(){
    char inicio[30];
    warningMessage("Digite uma tecla para continuar... ");
    scanf(" %[^\n]s",&inicio);
}

void successMessage(char message[]){
    printf("\033[0;32m"); 
    printf("%s",message);
    printf("\033[0m");
}

void errorMessage(char message[]){
    printf("\033[0;31m"); 
    printf("%s",message);
    printf("\033[0m");
}

void warningMessage(char message[]){
    printf("\033[0;33m"); 
    printf("%s",message);
    printf("\033[0m");

}