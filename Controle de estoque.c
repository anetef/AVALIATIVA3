#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
    int cd;
    char nome[50];
    int quantidade;
    char descricao[100];
    float preco;
    struct Produto *prox;
} Produto;

Produto *criarListaVazia(){   // função que inicializa uma lista vazia
    return NULL;
}

Produto *criarProduto(){     // função para criar codigos de produto
    Produto *novoProduto;
    novoProduto = (Produto *)malloc(sizeof(Produto));

    if (novoProduto == NULL){
        printf("Erro de alocacao\n");
        exit(EXIT_FAILURE);
    }
    novoProduto->cd = rand(); // usar rand para gerar codigos aleatorios para os produtos
    novoProduto->prox = NULL;
    return novoProduto;
}

void cadastrar(Produto **estoque){
    printf("\nCadastro dos Produtos-----------------------------------------------------------------------------------\n");

    Produto *novoProduto = criarProduto();

    printf("Digite o nome do produto: ");
    scanf("%s", novoProduto->nome);

    printf("Informe a quantidade do produto: ");
    scanf("%d", &novoProduto->quantidade);

    printf("Informe o preco individual do produto: ");
    scanf("%f", &novoProduto->preco);

    printf("Insira a descricao do produto: ");
    getchar(); // Limpar o buffer do teclado
    fgets(novoProduto->descricao, sizeof(novoProduto->descricao), stdin);
    novoProduto->descricao[strcspn(novoProduto->descricao, "\n")] = '\0';

    novoProduto->prox = *estoque;
    *estoque = novoProduto;

    printf("\nProduto cadastrado com sucesso!!!");
}

void adicionaProduto(Produto **estoque){

    printf("\nAdicionar novo produto a lista cadastrar\n");
    // chamar o novo codigo de um novo produto
    Produto *novoProduto = criarProduto();

    printf("Digite o nome do novo produto: ");
    scanf("%s", novoProduto->nome);

    printf("Descreva o produto:");
    getchar(); // Limpar o buffer do teclado
    fgets(novoProduto->descricao, sizeof(novoProduto->descricao), stdin);
    novoProduto->descricao[strcspn(novoProduto->descricao, "\n")] = '\0'; // Remover o caractere de nova linha

    printf("Informe a quantidade do produto: ");
    scanf("%d", &novoProduto->quantidade);

    printf("Informe o preco individual do produto: ");
    scanf("%f", &novoProduto->preco);

    novoProduto->prox = *estoque;
    *estoque = novoProduto;

    printf("Novo produto cadastrado com sucesso!!!\n");
}

void buscar(Produto *estoque){
    int cd;
    printf("Buscar Produto-------------------------------------------------------------------------------------\n");

    printf("Codigo do produto: ");
    scanf("%d", &cd);

    Produto *atual = estoque;

    while (atual != NULL)
    {
        if (atual->cd == cd)
        {
            printf("\nProduto encontrado------------------------------------------------------------------------------------- \n");
            printf("Codigo: %d\n", atual->cd);
            printf("Nome: %s\n", atual->nome);
            printf("Quantidade: %d\n", atual->quantidade);
            printf("Preco: %.2f\n", atual->preco);
            return;
        }
        atual = atual->prox;
    }

    printf("Produto nao encontrado!!!\n");
}
// imprimir todos os produtos
void imprimir(Produto *estoque){
    printf("Lista de Produtos -----------------------------------------------------------------------------------------------\n");

    Produto *atual = estoque;

    while (atual != NULL)
    {
        printf("Codigo: %d, Nome: %s, Descricao: %s, Quantidade: %d, Preco: %.2f\n",
               atual->cd, atual->nome, atual->descricao, atual->quantidade, atual->preco);
               printf("------------------------------------------------------------------------------------------------------------\n");
        atual = atual->prox;
    }
}

void excluir(Produto **estoque){
    int codigo;
    printf("Excluir Produto-------------------------------------------------------------------------------------------\n");

    printf("Insira o codigo do produto: ");
    scanf("%d", &codigo);

    Produto *atual = *estoque;
    Produto *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->cd == codigo){
            if (anterior == NULL){
                *estoque = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Produto removido com sucesso!!!\n");
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Produto nao encontrado!!!\n");
    return;
}
// função que percorre a lista de estoque e imprime um relatório com as informações de cada produto, incluindo código, descrição, quantidade e valor.
void imprimirRelatorioProduto(Produto *estoque){

    printf("\nRelatorio Dos Produtos---------------------------------------------------------------------------\n");

    Produto *atual = estoque;   // trazer o estoque dos produtos

    while (atual != NULL)   // se a lista atual for diferente de nulo imprima as caracteristicas da lista
    {
        printf("Codigo: %d\n", atual->cd);
        printf("Nome: %s\n", atual->nome);
        printf("Descricao: %s\n", atual->descricao);
        printf("Quantidade: %d\n", atual->quantidade);
        printf("Preco: %.2f\n", atual->preco);
        printf("Total do Estoque de Produtos: R$ %.2f\n", atual->quantidade * atual->preco);
        printf("------------------------------------------------------------------------------------\n");

        atual = atual->prox;   // atual lista deve receber os proximos detalhes da lista
    }
}
int main(){
    srand((unsigned int)time(NULL)); // gerar codigos diferentes
    Produto *estoque = criarListaVazia();
    int opcao;
    do{
        printf("\nDigite --------------------------------------------");
        printf("\n1 - Cadastrar Produto");
        printf("\n2 - Buscar Produto");
        printf("\n3 - Imprimir Estoque");
        printf("\n4 - Excluir Produto");
        printf("\n5 - Adicionar Novo Produto");
        printf("\n6 - Imprimir Relatorio Dos Produtos");
        printf("\n0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao){
        case 1:
            cadastrar(&estoque);
            break;
        case 2:
            buscar(estoque);
            break;
        case 3:
            imprimir(estoque);
            break;
        case 4:
            excluir(&estoque);
            break;
        case 5:
            adicionaProduto(&estoque);
            break;
        case 6:
            imprimirRelatorioProduto(estoque);
            break;
        case 0:
            printf("Programa encerrado!!!---------------------------------------------------------------:)\n");
            break;
        default:
            printf("Opcao invalida :( ----------Tente novamente!!!\n");
        }
    } while (opcao != 0);

    Produto *atual = estoque;
    while (atual != NULL){
        Produto *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}