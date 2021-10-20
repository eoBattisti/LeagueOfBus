typedef struct {
    //Campos a ser preenchidos
    char nome[50];
    int cpf;
    int poltrona;
} Cliente;

void opcaoSelect(int opcao, char *nomeArquivoCliente, char *nomeArquivoOnibus, Cliente vetor[], int tam);

void cadastrarCliente(char *nomeArquivoCliente, Cliente vetor[], int tam);

void reservarAcento();

void venderAcento();

void alterar();

void retirarPoltronaDaReserva();

void pesquisar();

void imprimir();

void excluirCadastro();
