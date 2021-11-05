#define TAMC 100
#define TAMP 40
#define ARQC "clientes.bin" 
#define ARQP "poltronas.bin"

typedef struct {
    //Campos a ser preenchidos
    char nome[50];
    char cpf[12];
    int poltrona;
} Cliente;

typedef struct{
    char cpfCliente[12];
    int status;
}Poltrona;

// Recebe as opções que o usuário digitar na main  e chama as funções
void opcaoSelect(int opcao, Cliente vetorClientes[], Poltrona vetorPoltronas[]);

// Função para espera 
void wait();

// Salva no arquivo o conteúdo do vetor
void salvarArquivo(Cliente vetorC[], Poltrona vetorP[]);

// Carrega os dados dos arquivos no vetor
void carregarArquivo(Cliente vetorC[], Poltrona vetorP[]);

// Opção de realizar o cadastro de clientes.
void cadastrarCliente(Cliente vetor[]);

// Opção de reservar assento ao cliente
void reservarAcento(Cliente Clientes[],Poltrona Poltronas[]);

// Opção de vender assento ao cliente
void venderAcento(Cliente vetorC[], Poltrona vetorP[]);

// Opção de alterar a poltrona de um cliente informado
void alterar(Cliente vetorC[], Poltrona vetorP[]);

// Opção de retirar a poltrona de um cliente
void retirarPoltronaDaReserva(Cliente vetorC[], Poltrona vetorP[]);

// Opção de pesquisar um cliente cadastrado por nome ou cpf
void pesquisar(Cliente vetorC[], Poltrona vetorP[]);

// Imprime os clientes ou as poltronas ao usuário
void imprimir(Cliente vetor[], Poltrona vetorP[], int opt);

// Opção de excluir o cadastro de algum cliente
void excluirCadastro(Cliente vetorC[],Poltrona vetorP[]);

// Zera os vetores e reseta os dados do sistema
void zerarVetores(Cliente Clientes[],Poltrona Poltronas[]);