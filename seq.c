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
    puts("buscarSeq: nao encontrado");
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
    puts("buscarBinSeq: nao encontrado");
}

// stubs para ordenação – implemente conforme PDF
void ordenarSelecao(int v[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            if (v[j] < v[min])
                min = j;
        }
        int tmp = v[i];
        v[i] = v[min];
        v[min] = tmp;
    }
}

void ordenarInsercao(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > chave) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = chave;
    }
}

void ordenarBolha(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                int tmp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = tmp;
            }
        }
    }
}

void ordenarShell(int v[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = v[i];
            int j;
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
                v[j] = v[j - gap];
            }
            v[j] = temp;
        }
    }
}

void ordenarQuick(int v[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = v[fim];
        int i = inicio - 1;

        for (int j = inicio; j < fim; j++) {
            if (v[j] < pivo) {
                i++;
                int tmp = v[i];
                v[i] = v[j];
                v[j] = tmp;
            }
        }

        int tmp = v[i+1];
        v[i+1] = v[fim];
        v[fim] = tmp;

        int pi = i + 1;

        ordenarQuick(v, inicio, pi - 1);
        ordenarQuick(v, pi + 1, fim);
    }
}
void merge(int v[], int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = v[inicio + i];
    for (int j = 0; j < n2; j++) R[j] = v[meio + 1 + j];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) v[k++] = L[i++];
        else v[k++] = R[j++];
    }

    while (i < n1) v[k++] = L[i++];
    while (j < n2) v[k++] = R[j++];
}

void ordenarMerge(int v[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        ordenarMerge(v, inicio, meio);
        ordenarMerge(v, meio + 1, fim);
        merge(v, inicio, meio, fim);
    }
}


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
