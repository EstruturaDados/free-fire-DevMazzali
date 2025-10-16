#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Struct Item
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// Enum CriterioOrdenacao
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

// Variáveis globais
Item mochila[10];
int numItens = 0;
int comparacoes = 0;
bool ordenadaPorNome = false;

// Protótipos das funções
void limparTela();
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void menuDeOrdenacao();
void insertionSort(CriterioOrdenacao criterio);
void buscaBinariaPorNome();

int main() {
    int opcao;
    
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer
        
        switch(opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                menuDeOrdenacao();
                break;
            case 5:
                buscaBinariaPorNome();
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
        
        if(opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
        
    } while(opcao != 0);
    
    return 0;
}

void limparTela() {
    for(int i = 0; i < 50; i++) {
        printf("\n");
    }
}

void exibirMenu() {
    limparTela();
    printf("========================================\n");
    printf("   CODIGO DA ILHA - SISTEMA DE MOCHILA\n");
    printf("========================================\n");
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Ordenar os itens por criterio\n");
    printf("5. Realizar busca binaria por nome\n");
    printf("0. Sair\n");
    printf("========================================\n");
    printf("Status: %s\n", ordenadaPorNome ? "Ordenada por nome" : "Nao ordenada por nome");
    printf("Itens na mochila: %d/10\n", numItens);
    printf("========================================\n");
}

void inserirItem() {
    if(numItens >= 10) {
        printf("\nMochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }
    
    printf("\n--- ADICIONAR NOVO ITEM ---\n");
    
    printf("Nome do item: ");
    fgets(mochila[numItens].nome, 50, stdin);
    mochila[numItens].nome[strcspn(mochila[numItens].nome, "\n")] = '\0';
    
    printf("Tipo do item: ");
    fgets(mochila[numItens].tipo, 30, stdin);
    mochila[numItens].tipo[strcspn(mochila[numItens].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochila[numItens].quantidade);
    
    do {
        printf("Prioridade (1 a 5): ");
        scanf("%d", &mochila[numItens].prioridade);
    } while(mochila[numItens].prioridade < 1 || mochila[numItens].prioridade > 5);
    
    getchar(); // Limpa o buffer
    
    numItens++;
    ordenadaPorNome = false;
    
    printf("\nItem adicionado com sucesso!\n");
}

void removerItem() {
    if(numItens == 0) {
        printf("\nMochila vazia! Nao ha itens para remover.\n");
        return;
    }
    
    char nomeBusca[50];
    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    int encontrado = -1;
    for(int i = 0; i < numItens; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }
    
    if(encontrado != -1) {
        // Reorganiza o vetor
        for(int i = encontrado; i < numItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        numItens--;
        printf("\nItem removido com sucesso!\n");
    } else {
        printf("\nItem nao encontrado na mochila.\n");
    }
}

void listarItens() {
    if(numItens == 0) {
        printf("\nMochila vazia! Nenhum item para exibir.\n");
        return;
    }
    
    printf("\n--- ITENS NA MOCHILA ---\n");
    printf("%-20s %-15s %-10s %-10s\n", "NOME", "TIPO", "QUANT.", "PRIORID.");
    printf("-----------------------------------------------------------\n");
    
    for(int i = 0; i < numItens; i++) {
        printf("%-20s %-15s %-10d %-10d\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade, 
               mochila[i].prioridade);
    }
    printf("-----------------------------------------------------------\n");
    printf("Total de itens: %d\n", numItens);
}

void menuDeOrdenacao() {
    if(numItens == 0) {
        printf("\nMochila vazia! Nao ha itens para ordenar.\n");
        return;
    }
    
    int opcao;
    printf("\n--- MENU DE ORDENACAO ---\n");
    printf("1. Ordenar por nome (alfabetica)\n");
    printf("2. Ordenar por tipo (alfabetica)\n");
    printf("3. Ordenar por prioridade (maior para menor)\n");
    printf("Escolha o criterio: ");
    scanf("%d", &opcao);
    getchar();
    
    comparacoes = 0;
    
    switch(opcao) {
        case 1:
            insertionSort(ORDENAR_NOME);
            ordenadaPorNome = true;
            printf("\nItens ordenados por nome!\n");
            break;
        case 2:
            insertionSort(ORDENAR_TIPO);
            ordenadaPorNome = false;
            printf("\nItens ordenados por tipo!\n");
            break;
        case 3:
            insertionSort(ORDENAR_PRIORIDADE);
            ordenadaPorNome = false;
            printf("\nItens ordenados por prioridade!\n");
            break;
        default:
            printf("\nOpcao invalida!\n");
            return;
    }
    
    printf("Numero de comparacoes realizadas: %d\n", comparacoes);
    listarItens();
}

void insertionSort(CriterioOrdenacao criterio) {
    for(int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        
        bool condicao;
        
        while(j >= 0) {
            comparacoes++;
            
            switch(criterio) {
                case ORDENAR_NOME:
                    condicao = strcmp(mochila[j].nome, chave.nome) > 0;
                    break;
                case ORDENAR_TIPO:
                    condicao = strcmp(mochila[j].tipo, chave.tipo) > 0;
                    break;
                case ORDENAR_PRIORIDADE:
                    condicao = mochila[j].prioridade < chave.prioridade;
                    break;
                default:
                    condicao = false;
            }
            
            if(condicao) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        
        mochila[j + 1] = chave;
    }
}

void buscaBinariaPorNome() {
    if(numItens == 0) {
        printf("\nMochila vazia! Nao ha itens para buscar.\n");
        return;
    }
    
    if(!ordenadaPorNome) {
        printf("\nAVISO: A mochila precisa estar ordenada por nome!\n");
        printf("Deseja ordenar agora? (1-Sim, 0-Nao): ");
        int opcao;
        scanf("%d", &opcao);
        getchar();
        
        if(opcao == 1) {
            comparacoes = 0;
            insertionSort(ORDENAR_NOME);
            ordenadaPorNome = true;
            printf("\nItens ordenados por nome!\n");
        } else {
            return;
        }
    }
    
    char nomeBusca[50];
    printf("\n--- BUSCA BINARIA ---\n");
    printf("Digite o nome do item a buscar: ");
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    int esquerda = 0;
    int direita = numItens - 1;
    int encontrado = -1;
    int comparacoesBusca = 0;
    
    while(esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        comparacoesBusca++;
        
        int resultado = strcmp(mochila[meio].nome, nomeBusca);
        
        if(resultado == 0) {
            encontrado = meio;
            break;
        } else if(resultado < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    printf("\nComparacoes realizadas na busca: %d\n", comparacoesBusca);
    
    if(encontrado != -1) {
        printf("\n*** ITEM ENCONTRADO ***\n");
        printf("Nome: %s\n", mochila[encontrado].nome);
        printf("Tipo: %s\n", mochila[encontrado].tipo);
        printf("Quantidade: %d\n", mochila[encontrado].quantidade);
        printf("Prioridade: %d\n", mochila[encontrado].prioridade);
    } else {
        printf("\nItem nao encontrado na mochila.\n");
    }
}
