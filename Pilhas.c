/* ENUNCIADO
Um  estacionamento  contém  uma  única alameda  que  guarda  até  5  carros.  
Existe  apenas  uma entrada/saída no estacionamento, em uma extremidade da alameda.
Se  chegar  um  cliente  para  retirar  um  carro  que  não  seja  o mais  próximo  da  saída,  todos  os  carros bloqueando  seu 
caminho  sairão  do  estacionamento,  o  carro  do  cliente  será  manobrado  para  fora  do estacionamento, e os 
outros carros voltarão a ocupar a mesma sequência inicial.
Escreva um programa que processe um grupo de linhas de entrada. 
Cada linha de entrada contém um 'E',  de  entrada,  ou  um  'S',  de  saída,  e  o  número  da  placa  do  carro. 
Presume-se  que  os  carros  cheguem  e partam na ordem especificada pela entrada.
A  solução  do  problema  deve  ser  implementada  obrigatoriamente  com  a  utilização  de  estruturas  de pilha.
O  programa  deve  imprimir  uma  mensagem  sempre  que  um  carro  chegar  ou  sair.
Quando  um  carro chegar, a mensagem deve especificar se existe ou não vaga para o carro no estacionamento. 
Se não houver vaga, o carro partirá sem entrar no estacionamento. Quando um carro sair do estacionamento, a mensagem deverá incluir 
o número de vezes em que o carro foi manobrado para fora do estacionamento para permitir que outros carros saíssem.
Assumir que a placa de um carro possui 7 letras/dígitos.
DICA: Para não precisar digitar os dados de entrada e saída a cada execução faça sua inicialização dentro do programa.
*/

// Atividade Avaliativa 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char placaCarro[8];
} Carro;

typedef struct nodulo {
    Carro carro;
    struct nodulo *proximo;
} Nodulo;

typedef struct {
    Nodulo *topo;
    int tamanho;
    int capacidade;
} Pilha;

void alocarCarro(Pilha *vagasEstacionamento, const char *placaCarro) {
    Nodulo *auxiliar = vagasEstacionamento->topo;
    while (auxiliar) {
        if (strcmp(auxiliar->carro.placaCarro, placaCarro) == 0) {
            printf("Carro com a placa %s ja esta estacionado.\n", placaCarro);
            return;
        }
        auxiliar = auxiliar->proximo;
    }

    if (vagasEstacionamento->tamanho >= vagasEstacionamento->capacidade) {
        printf("Nao ha vagas disponiveis.\n");
        printf("O carro com a placa %s nao pode estacionar.\n", placaCarro); 
        return;
    }

    Nodulo *novo = (Nodulo *)malloc(sizeof(Nodulo));

    if (novo) {
        strcpy(novo->carro.placaCarro, placaCarro);
        novo->proximo = vagasEstacionamento->topo;\
        vagasEstacionamento->topo = novo;
        vagasEstacionamento->tamanho++;

        printf("Carro com a placa %s foi estacionado.\n", novo->carro.placaCarro);
    } else {
        printf("Erro ao alocar memoria.\n");
    }
}

void imprimirCarros(Pilha *vagasEstacionamento) {
    system("cls");
    Nodulo *auxiliar = vagasEstacionamento->topo;

    printf("=============================================\n");
    printf("             CARROS ESTACIONADOS             \n");
    printf("=============================================\n");
    while (auxiliar) {
        printf("Placa: %s\n", auxiliar->carro.placaCarro);
        auxiliar = auxiliar->proximo;
    }
    printf("\n");
}

void removerCarro(Pilha *vagasEstacionamento, const char *placaCarro) {
    Pilha vagas;
    vagas.topo = NULL;
    vagas.tamanho = 0;
    vagas.capacidade = vagasEstacionamento->capacidade;
    Nodulo *removido = NULL;
    int manobrasDadas = 0;

    while (vagasEstacionamento->topo != NULL && strcmp(vagasEstacionamento->topo->carro.placaCarro, placaCarro) != 0) {
        removido = vagasEstacionamento->topo;
        vagasEstacionamento->topo = removido->proximo;
        vagasEstacionamento->tamanho--;
        removido->proximo = vagas.topo;
        vagas.topo = removido;
        vagas.tamanho++;
        manobrasDadas++;
    }

    if (vagasEstacionamento->topo != NULL && strcmp(vagasEstacionamento->topo->carro.placaCarro, placaCarro) == 0) {
        removido = vagasEstacionamento->topo;
        vagasEstacionamento->topo = removido->proximo;
        vagasEstacionamento->tamanho--;
        free(removido);
        printf("Carro com a placa %s foi removido.\n", placaCarro);
        printf("O carro foi manobrado %d vezes.\n", manobrasDadas);
    } else {
        printf("Carro com a placa %s não encontrado.\n", placaCarro);
    }

    while (vagas.topo != NULL) {
        removido = vagas.topo;
        vagas.topo = removido->proximo;
        vagas.tamanho--;
        removido->proximo = vagasEstacionamento->topo;
        vagasEstacionamento->topo = removido;
        vagasEstacionamento->tamanho++;
    }
}

void exibirMenu(Pilha *vagasEstacionamento) {
    int opcao;
    do {
        system("cls");
        printf("===========================\n");
        printf("      ESTACIONAMENTO       \n");
        printf("===========================\n");
        printf("1. Listar carros           \n");
        printf("2. Entrar com carro        \n");
        printf("3. Sair com carro          \n");
        printf("0. Sair                    \n");
        printf("===========================\n");
        printf("Selecione sua opcao --> ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                imprimirCarros(vagasEstacionamento);
                break;
            case 2: {
                char placa[8];
                printf("Digite a placa do carro que vai entrar no estacionamento (7 caracteres): ");
                scanf("%s", placa);
                alocarCarro(vagasEstacionamento, placa);
                break;
            }
            case 3: {
                char placa[8];
                imprimirCarros(vagasEstacionamento);
                printf("Digite a placa do carro que vai sair do estacionamento: ");
                scanf("%s", placa);
                removerCarro(vagasEstacionamento, placa);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

        system("pause");

    } while (opcao != 0);
}

int main() {
    Pilha vagasEstacionamento;
    vagasEstacionamento.topo = NULL;
    vagasEstacionamento.tamanho = 0;
    vagasEstacionamento.capacidade = 5;

    // CARROS ALOCADOS AUTOMATICAMENTE - INÍCIO
    system ("CLS");
    alocarCarro(&vagasEstacionamento, "IJK7L89");
    system ("PAUSE");
    system ("CLS");
    alocarCarro(&vagasEstacionamento, "MNO0P12");
    system ("PAUSE");
    system ("CLS");
    alocarCarro(&vagasEstacionamento, "QRS3T45");
    system ("PAUSE");
    system ("CLS");
    alocarCarro(&vagasEstacionamento, "LQV1D23");
    system ("PAUSE");
    system ("CLS");
    alocarCarro(&vagasEstacionamento, "EFG4H56");
    system ("PAUSE");
    system ("CLS");
    alocarCarro(&vagasEstacionamento, "UVW6X78");
    system ("PAUSE");
    system ("CLS");

    exibirMenu(&vagasEstacionamento);

    return 0;
}

