#include <stdio.h>
#include "lib_seq.h"
#include "lib_enc.h"

void menuSequencial(ListaSeq *L) {
    int op; char nome[MAX_NOME]; int rg, pos;
    char arquivo[100];
    do {
        printf(
            "\nMenu Sequencial:\n"
            " 1) Inserir inicio\n"
            " 2) Inserir fim\n"
            " 3) Inserir N\n"
            " 4) Remover inicio\n"
            " 5) Remover fim\n"
            " 6) Remover N\n"
            " 7) Buscar RG\n"
            " 8) Mostrar\n"
            " 9) Salvar em arquivo\n"
            "10) Carregar de arquivo\n"
            "11) Sair\n"
            ">> "
        );
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("Nome? ");    scanf(" %49[^\n]", nome);
                printf("RG? ");      scanf("%d", &rg);
                inserirInicioSeq(L, nome, rg);
                break;
            case 2:
                printf("Nome? ");    scanf(" %49[^\n]", nome);
                printf("RG? ");      scanf("%d", &rg);
                inserirFimSeq(L, nome, rg);
                break;
            case 3:
                printf("Pos? ");     scanf("%d", &pos);
                printf("Nome? ");    scanf(" %49[^\n]", nome);
                printf("RG? ");      scanf("%d", &rg);
                inserirPosicaoSeq(L, nome, rg, pos);
                break;
            case 4:
                removerInicioSeq(L);
                break;
            case 5:
                removerFimSeq(L);
                break;
            case 6:
                printf("Pos? ");     scanf("%d", &pos);
                removerPosicaoSeq(L, pos);
                break;
            case 7:
                printf("RG? ");      scanf("%d", &rg);
                printf("1) Sequencial  2) Binaria\n>> ");
                {
                    int m; scanf("%d", &m);
                    if (m == 1) buscarSeq(L, rg);
                    else        buscarBinSeq(L, rg);
                }
                break;
            case 8:
                imprimirListaSeq(L);
                break;
            case 9:
                printf("Nome do arquivo para salvar: ");
                scanf(" %99s", arquivo);
                gravarArquivoSeq(L, arquivo);
                break;
            case 10:
                printf("Nome do arquivo para carregar: ");
                scanf(" %99s", arquivo);
                lerArquivoSeq(L, arquivo);
                break;
            case 11:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção invalida\n");
        }
    } while (op != 11);
}

void menuEncadeada(Node **head) {
    int op; char nome[MAX_NOME]; int rg, pos;
    char arquivo[100];
    do {
        printf(
            "\nMenu Encadeada:\n"
            " 1) Inserir inicio\n"
            " 2) Inserir fim\n"
            " 3) Inserir N\n"
            " 4) Remover inicio\n"
            " 5) Remover fim\n"
            " 6) Remover N\n"
            " 7) Buscar RG\n"
            " 8) Mostrar\n"
            " 9) Salvar em arquivo\n"
            "10) Carregar de arquivo\n"
            "11) Sair\n"
            ">> "
        );
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("Nome? ");    scanf(" %49[^\n]", nome);
                printf("RG? ");      scanf("%d", &rg);
                inserirInicioEnc(head, nome, rg);
                break;
            case 2:
                printf("Nome? ");    scanf(" %49[^\n]", nome);
                printf("RG? ");      scanf("%d", &rg);
                inserirFimEnc(head, nome, rg);
                break;
            case 3:
                printf("Qual a posicao? ");     scanf("%d", &pos);
                printf("Nome? ");    scanf(" %49[^\n]", nome);
                printf("RG? ");      scanf("%d", &rg);
                inserirPosicaoEnc(head, nome, rg, pos);
                break;
            case 4:
                removerInicioEnc(head);
                break;
            case 5:
                removerFimEnc(head);
                break;
            case 6:
                printf("Qual a posicao? ");     scanf("%d", &pos);
                removerPosicaoEnc(head, pos);
                break;
            case 7:
                printf("Digite o RG: ");      scanf("%d", &rg);
                buscarEnc(*head, rg);
                break;
            case 8:
                imprimirListaEnc(*head);
                break;
            case 9:
                printf("Nome do arquivo para salvar: ");
                scanf(" %99s", arquivo);
                gravarArquivoEnc(*head, arquivo);
                break;
            case 10:
                printf("Nome do arquivo para carregar: ");
                scanf(" %99s", arquivo);
                *head = lerArquivoEnc(arquivo);
                break;
            case 11:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção invalida\n");
        }
    } while (op != 11);
}
