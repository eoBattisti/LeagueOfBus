typedef struct {
    //Campos a ser preenchidos
    char nome[50];
    int cpf;
    int poltrona;
} Cliente;

typedef struct{
    int cpfCliente;
    int status;
}Poltronas;

void opcaoSelect(int opcao, char *nomeArquivoCliente, char *nomeArquivoOnibus, Cliente vetor[], int tam);

void cadastrarCliente(char *nomeArquivoCliente, Cliente vetor[], int tam);

void reservarAcento();

void venderAcento();

void alterar();

void retirarPoltronaDaReserva();

void pesquisar();

void imprimir(char *nomeArquivoCliente, Cliente vetor[], int tam);

void imprimirOnibus(Poltronas assentos[]);

void criarOnibus(Poltronas assentos[]);

void excluirCadastro();

void carregarArquivo(char *nomeArquivo, Cliente vetor[], int tam);