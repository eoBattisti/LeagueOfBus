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

void cadastrarCliente(Cliente vetor[]);

void reservarAcento();

void venderAcento();

void alterar();

void retirarPoltronaDaReserva();

void pesquisar();

void imprimir(Cliente vetor[], Poltrona vetorP[]);

void imprimirOnibus();

void excluirCadastro();

void carregarArquivo(Cliente vetorC[], Poltrona vetorP[]);