// menu.c — Menus com escolhas numéricas em arquivo separado
#include <stdio.h>
#include "lib_seq.h"
#include "lib_enc.h"

void menuSequencial(ListaSeq *L) {
    int op;
    char nome[MAX_NOME];
    int rg, pos;
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
            " 8) Ordenar\n"
            " 9) Mostrar\n"
            "10) Salvar\n"
            "11) Carregar\n"
            "12) Sair\n"
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
                printf("1) Sequencial  2) Binária\n>> ");
                {
                    int m; scanf("%d",&m);
                    if (m==1) buscarSeq(L, rg);
                    else      buscarBinSeq(L, rg);
                }
                break;
            case 8:
                printf(
                    "Algoritmos de Ordenação:\n"
                    " 1) Seleco\n"
                    " 2) Insero\n"
                    " 3) Bolha\n"
                    " 4) Shell\n"
                    " 5) Quick\n"
                    " 6) Merge\n"
                    ">> "
                );
                {
                    //IMPLEMENTAR AS FUNCOES 
                    int m; scanf("%d",&m);
                    switch (m) {
                        case 1: ordenarSelecao(L);    break;
                        case 2: ordenarInsercao(L);   break;
                        case 3: ordenarBolha(L);      break;
                        case 4: ordenarShell(L);      break;
                        case 5: ordenarQuick(L);      break;
                        case 6: ordenarMerge(L);      break;
                        default: printf("Opção invalida\n");
                    }
                }
                break;
            case 9:
                imprimirListaSeq(L);
                break;
            case 10:
                gravarArquivoSeq(L, "seq.txt");
                break;
            case 11:
                lerArquivoSeq(L, "seq.txt");
                break;
            case 12:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção invalida\n");
        }
    } while (op != 12);
}

void menuEncadeada(Node **head) {
    int op;
    char nome[MAX_NOME];
    int rg, pos;
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
            " 9) Salvar\n"
            "10) Carregar\n"
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
                printf("Pos? ");     scanf("%d", &pos);
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
                printf("Pos? ");     scanf("%d", &pos);
                removerPosicaoEnc(head, pos);
                break;
            case 7:
                printf("RG? ");      scanf("%d", &rg);
                buscarEnc(*head, rg);
                break;
            case 8:
                imprimirListaEnc(*head);
                break;
            case 9:
                gravarArquivoEnc(*head, "enc.txt");
                break;
            case 10:
                *head = lerArquivoEnc("enc.txt");
                break;
            case 11:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção invalida\n");
        }
    } while (op != 11);
}
