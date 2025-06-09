#include "lib_seq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void garantirCapacidade(ListaSeq *L) {
    if (L->tamanho >= L->capacidade) {
        L->capacidade = L->capacidade ? L->capacidade * 2 : 10;
        L->itens = realloc(L->itens, sizeof(Item) * L->capacidade);
    }
}

void criarListaSeq(ListaSeq *L) {
    L->itens      = NULL;
    L->tamanho    = 0;
    L->capacidade = 0;
}

void liberarListaSeq(ListaSeq *L) {
    free(L->itens);
    L->itens = NULL;
    L->tamanho = L->capacidade = 0;
}

#define MET_START  clock_t _t0 = clock(); long C=0, M=0;
#define MET_END(msg) \
    printf(msg " ⇒ C(n)=%ld, M(n)=%ld, tempo=%.6fs\n", \
           C, M, (double)(clock()-_t0)/CLOCKS_PER_SEC)

void inserirInicioSeq(ListaSeq *L, const char *nome, int rg) {
    MET_START;
    garantirCapacidade(L);
    for (int i = L->tamanho; i > 0; --i) {
        L->itens[i] = L->itens[i-1]; M++;
    }
    strncpy(L->itens[0].nome, nome, MAX_NOME);
    L->itens[0].rg = rg; M++;
    L->tamanho++;
    printf("Inserido: %s, %d, posição: 0\n", nome, rg);
    MET_END("inserirInicioSeq");
}

void inserirFimSeq(ListaSeq *L, const char *nome, int rg) {
    MET_START;
    garantirCapacidade(L);
    int pos = L->tamanho++;
    strncpy(L->itens[pos].nome, nome, MAX_NOME);
    L->itens[pos].rg = rg; M++;
    printf("Inserido: %s, %d, posição: %d\n", nome, rg, pos);
    MET_END("inserirFimSeq");
}

void inserirPosicaoSeq(ListaSeq *L, const char *nome, int rg, int pos) {
    MET_START;
    garantirCapacidade(L);
    for (int i = L->tamanho; i > pos; --i) {
        L->itens[i] = L->itens[i-1]; M++;
    }
    strncpy(L->itens[pos].nome, nome, MAX_NOME);
    L->itens[pos].rg = rg; M++;
    L->tamanho++;
    printf("Inserido: %s, %d, posição: %d\n", nome, rg, pos);
    MET_END("inserirPosicaoSeq");
}

void removerInicioSeq(ListaSeq *L) {
    MET_START;
    if (L->tamanho == 0) return;
    printf("Removido: %s, %d, posição: 0\n", L->itens[0].nome, L->itens[0].rg);
    for (int i = 0; i + 1 < L->tamanho; ++i) {
        L->itens[i] = L->itens[i+1]; M++;
    }
    L->tamanho--;
    MET_END("removerInicioSeq");
}

void removerFimSeq(ListaSeq *L) {
    MET_START;
    if (L->tamanho == 0) return;
    printf("Removido: %s, %d, posição: %d\n", L->itens[L->tamanho-1].nome, L->itens[L->tamanho-1].rg, L->tamanho-1);
    L->tamanho--;
    MET_END("removerFimSeq");
}

void removerPosicaoSeq(ListaSeq *L, int pos) {
    MET_START;
    if (pos < 0 || pos >= L->tamanho) {
        printf("Posição inválida\n");
        return;
    }
    printf("Removido: %s, %d, posição: %d\n", L->itens[pos].nome, L->itens[pos].rg, pos);
    for (int i = pos; i + 1 < L->tamanho; ++i) {
        L->itens[i] = L->itens[i+1]; M++;
    }
    L->tamanho--;
    MET_END("removerPosicaoSeq");
}

void buscarSeq(ListaSeq *L, int rg) {
    MET_START;
    for (int i = 0; i < L->tamanho; ++i) {
        C++;
        if (L->itens[i].rg == rg) {
            printf("Encontrado: %s, %d, posição: %d\n", L->itens[i].nome, L->itens[i].rg, i);
            MET_END("buscarSeq");
            return;
        }
    }
    printf("buscarSeq: não encontrado\n");
}

void buscarBinSeq(ListaSeq *L, int rg) {
    MET_START;
    int lo = 0, hi = L->tamanho - 1;
    while (lo <= hi) {
        int m = (lo + hi) / 2; C++;
        if (L->itens[m].rg == rg) {
            printf("Encontrado: %s, %d, posição: %d\n", L->itens[m].nome, L->itens[m].rg, m);
            MET_END("buscarBinSeq");
            return;
        }
        if (L->itens[m].rg < rg) lo = m + 1;
        else hi = m - 1;
    }
    printf("buscarBinSeq: não encontrado\n");
}

// Os métodos de ordenação e I/O permanecem como estão, só adicione printf nas exibições de elementos, se quiser mostrar posição.

void imprimirListaSeq(ListaSeq *L) {
    for (int i = 0; i < L->tamanho; ++i) {
        printf("%d: %s,%d\n", i, L->itens[i].nome, L->itens[i].rg);
    }
}

void gravarArquivoSeq(ListaSeq *L, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "w");
    for (int i = 0; i < L->tamanho; ++i) {
        fprintf(f, "%s,%d\n", L->itens[i].nome, L->itens[i].rg);
    }
    fclose(f);
}

void lerArquivoSeq(ListaSeq *L, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (!f) return;
    criarListaSeq(L);
    char linha[128], nome[MAX_NOME];
    int rg;
    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, " %49[^,],%d", nome, &rg) == 2) {
            inserirFimSeq(L, nome, rg);
        }
    }
    fclose(f);
}
