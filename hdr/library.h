typedef struct {
    //Campos a ser preenchidos
    char nome[50];
    char cpf[11];
    int poltrona;
} Cliente;

typedef struct{
    int cpfCliente;
    int status;
}Poltronas;

void opcaoSelect(int opcao,  Cliente vetor[]);

void cadastrarCliente();

void reservarAcento();

void venderAcento();

void alterar();

void retirarPoltronaDaReserva();

void pesquisar();

void imprimir();

void imprimirOnibus(Poltronas assentos[]);

void criarOnibus(Poltronas assentos[]);

void excluirCadastro();

void carregarArquivo(char *nomeArquivo, Cliente vetor[], int tam);

int verificarCliente(char cpf[], Cliente v[],int tam);
