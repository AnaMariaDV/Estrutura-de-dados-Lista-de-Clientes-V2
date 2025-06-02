// seq.c — Implementação da Lista Sequencial (sem menu)
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
    L->itens     = NULL;
    L->tamanho   = 0;
    L->capacidade= 0;
}

void liberarListaSeq(ListaSeq *L) {
    free(L->itens);
    L->itens = NULL;
    L->tamanho = L->capacidade = 0;
}

#define MET_START  clock_t _t0 = clock(); long C=0, M=0;
#define MET_END(msg,pos) \
    printf(msg " ⇒ C(n)=%ld, M(n)=%ld, tempo=%.6fs, pos=%d\n", \
           C, M, (double)(clock()-_t0)/CLOCKS_PER_SEC, pos);

void inserirInicioSeq(ListaSeq *L, const char *nome, int rg) {
    MET_START;
    garantirCapacidade(L);
    for (int i = L->tamanho; i > 0; --i) { L->itens[i] = L->itens[i-1]; M++; }
    strncpy(L->itens[0].nome, nome, MAX_NOME);
    L->itens[0].rg = rg; M++;
    L->tamanho++;
    MET_END("inserirInicioSeq", 0);
}

void inserirFimSeq(ListaSeq *L, const char *nome, int rg) {
    MET_START;
    garantirCapacidade(L);
    int pos = L->tamanho++;
    strncpy(L->itens[pos].nome, nome, MAX_NOME);
    L->itens[pos].rg = rg; M++;
    MET_END("inserirFimSeq", pos);
}

void inserirPosicaoSeq(ListaSeq *L, const char *nome, int rg, int pos) {
    MET_START;
    garantirCapacidade(L);
    for (int i = L->tamanho; i > pos; --i) { L->itens[i] = L->itens[i-1]; M++; }
    strncpy(L->itens[pos].nome, nome, MAX_NOME);
    L->itens[pos].rg = rg; M++;
    L->tamanho++;
    MET_END("inserirPosicaoSeq", pos);
}

void removerInicioSeq(ListaSeq *L) {
    MET_START;
    for (int i = 0; i + 1 < L->tamanho; ++i) { L->itens[i] = L->itens[i+1]; M++; }
    L->tamanho--;
    MET_END("removerInicioSeq", 0);
}

void removerFimSeq(ListaSeq *L) {
    MET_START;
    int pos = L->tamanho - 1;
    L->tamanho--;
    MET_END("removerFimSeq", pos);
}

void removerPosicaoSeq(ListaSeq *L, int pos) {
    MET_START;
    for (int i = pos; i + 1 < L->tamanho; ++i) { L->itens[i] = L->itens[i+1]; M++; }
    L->tamanho--;
    MET_END("removerPosicaoSeq", pos);
}

void buscarSeq(ListaSeq *L, int rg) {
    MET_START;
    for (int i = 0; i < L->tamanho; ++i) {
        C++;
        if (L->itens[i].rg == rg) {
            MET_END("buscarSeq", i);
            return;
        }
    }
    puts("buscarSeq: não encontrado");
}

void buscarBinSeq(ListaSeq *L, int rg) {
    MET_START;
    int lo = 0, hi = L->tamanho - 1;
    while (lo <= hi) {
        int m = (lo + hi) / 2; C++;
        if (L->itens[m].rg == rg) {
            MET_END("buscarBinSeq", m);
            return;
        }
        if (L->itens[m].rg < rg) lo = m + 1;
        else hi = m - 1;
    }
    puts("buscarBinSeq: não encontrado");
}

// stubs para ordenação – implemente conforme PDF
void ordenarSelecao (ListaSeq *L) { /* ... */ }
void ordenarInsercao(ListaSeq *L) { /* ... */ }
void ordenarBolha   (ListaSeq *L) { /* ... */ }
void ordenarShell   (ListaSeq *L) { /* ... */ }
void ordenarQuick   (ListaSeq *L) { /* ... */ }
void ordenarMerge   (ListaSeq *L) { /* ... */ }

void imprimirListaSeq(ListaSeq *L) {
    for (int i = 0; i < L->tamanho; ++i)
        printf("%s,%d\n", L->itens[i].nome, L->itens[i].rg);
}

void gravarArquivoSeq(ListaSeq *L, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "w");
    for (int i = 0; i < L->tamanho; ++i)
        fprintf(f, "%s,%d\n", L->itens[i].nome, L->itens[i].rg);
    fclose(f);
}

void lerArquivoSeq(ListaSeq *L, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (!f) return;
    criarListaSeq(L);
    char nome[MAX_NOME];
    int rg;
    while (fscanf(f, " %49[^,],%d", nome, &rg) == 2)
        inserirFimSeq(L, nome, rg);
    fclose(f);
}
