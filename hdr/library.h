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

void opcaoSelect(int opcao, Cliente vetorClientes[], Poltrona vetorPoltronas[]);

void salvarArquivo(Cliente vetorC[], Poltrona vetorP[]);

void carregarArquivo(Cliente vetorC[], Poltrona vetorP[]);

void cadastrarCliente(Cliente vetor[]);

void reservarAcento(Cliente Clientes[],Poltrona Poltronas[]);

void venderAcento(Cliente vetorC[], Poltrona vetorP[]);

void alterar(Cliente vetorC[], Poltrona vetorP[]);

void retirarPoltronaDaReserva(Cliente vetorC[], Poltrona vetorP[]);

void pesquisar();

void imprimir(Cliente vetor[], Poltrona vetorP[], int opt);

void excluirCadastro();

void zerarVetores(Cliente Clientes[],Poltrona Poltronas[]);