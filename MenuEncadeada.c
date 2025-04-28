#include"libEncadeada.h"
void menu(Node **cabeca) {
    int opcao;
    do {
        printf("\n=== Menu de Operacoes (Lista Encadeada com Metricas) ===\n");
        printf("1. Inserir no inicio\n");
        printf("2. Inserir no fim\n");
        printf("3. Inserir na posicao N\n");
        printf("4. Retirar do inicio\n");
        printf("5. Retirar do fim\n");
        printf("6. Retirar da posicao N\n");
        printf("7. Buscar por RG\n");
        printf("8. Mostrar a lista\n");
        printf("9. Salvar a lista em um arquivo\n");
        printf("10. Ler a lista de um arquivo\n");
        printf("0. Sair do sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: {
                char nome[50];
                int rg;
                printf("Entre com o nome: ");
                scanf("%s", nome);
                printf("Entre com o RG (9 algarismos): ");
                scanf("%d", &rg);
                inserirNoInicio(cabeca, nome, rg);
                break;
            }
            case 2: {
                char nome[50];
                int rg;
                printf("Entre com o nome: ");
                scanf("%s", nome);
                printf("Entre com o RG (9 algarismos): ");
                scanf("%d", &rg);
                inserirNoFim(cabeca, nome, rg);
                break;
            }
            case 3: {
                char nome[50];
                int rg, posDesejada;
                printf("Entre com o nome: ");
                scanf("%s", nome);
                printf("Entre com o RG (9 algarismos): ");
                scanf("%d", &rg);
                printf("Entre com a posicao desejada: ");
                scanf("%d", &posDesejada);
                inserirNoPosicao(cabeca, nome, rg, posDesejada);
                break;
            }
            case 4: {
                removerNoInicio(cabeca);
                break;
            }
            case 5: {
                removerNoFim(cabeca);
                break;
            }
            case 6: {
                int posDesejada;
                printf("Entre com a posicao para remocao: ");
                scanf("%d", &posDesejada);
                removerNoPosicao(cabeca, posDesejada);
                break;
            }
            case 7: {
                int rg;
                printf("Entre com o RG para busca: ");
                scanf("%d", &rg);
                procurarPorRG(*cabeca, rg);
                break;
            }
            case 8: {
                imprimirLista(*cabeca);
                break;
            }
            case 9: {
                char nomeArquivo[100];
                printf("Entre com o nome do arquivo para salvar: ");
                scanf("%s", nomeArquivo);
                salvarLista(*cabeca, nomeArquivo);
                break;
            }
            case 10: {
                char nomeArquivo[100];
                printf("Entre com o nome do arquivo para ler: ");
                scanf("%s", nomeArquivo);
                lerLista(cabeca, nomeArquivo);
                break;
            }
            case 0: {
                sairDoSistema();
                break;
            }
            default: {
                printf("Opcao invalida! Tente novamente.\n");
                break;
            }
        }
    } while(opcao != 0);
}