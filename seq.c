// seq.c — Implementação da Lista Sequencial
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
    MET_END("inserirInicioSeq");
}

void inserirFimSeq(ListaSeq *L, const char *nome, int rg) {
    MET_START;
    garantirCapacidade(L);
    int pos = L->tamanho++;
    strncpy(L->itens[pos].nome, nome, MAX_NOME);
    L->itens[pos].rg = rg; M++;
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
    MET_END("inserirPosicaoSeq");
}

void removerInicioSeq(ListaSeq *L) {
    MET_START;
    for (int i = 0; i + 1 < L->tamanho; ++i) {
        L->itens[i] = L->itens[i+1]; M++;
    }
    L->tamanho--;
    MET_END("removerInicioSeq");
}

void removerFimSeq(ListaSeq *L) {
    MET_START;
    L->tamanho--;
    MET_END("removerFimSeq");
}

void removerPosicaoSeq(ListaSeq *L, int pos) {
    MET_START;
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
            MET_END("buscarSeq");
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
            MET_END("buscarBinSeq");
            return;
        }
        if (L->itens[m].rg < rg) lo = m + 1;
        else hi = m - 1;
    }
    puts("buscarBinSeq: não encontrado");
}

// Selection Sort
void selectionSort(ListaSeq *L) {
    MET_START;
    int n = L->tamanho;
    for (int i = 0; i < n - 1; ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j) {
            C++;
            if (L->itens[j].rg < L->itens[min].rg) {
                min = j;
            }
        }
        if (min != i) {
            Item tmp = L->itens[i];
            L->itens[i] = L->itens[min];
            L->itens[min] = tmp;
            M += 3;
        }
    }
    MET_END("selectionSort");
}

// Insertion Sort
void insertionSort(ListaSeq *L) {
    MET_START;
    int n = L->tamanho;
    for (int i = 1; i < n; ++i) {
        Item key = L->itens[i]; M++;
        int j = i - 1;
        while (j >= 0) {
            C++;
            if (L->itens[j].rg > key.rg) {
                L->itens[j + 1] = L->itens[j]; M++;
                j--;
            } else {
                break;
            }
        }
        L->itens[j + 1] = key; M++;
    }
    MET_END("insertionSort");
}

// Bubble Sort
void bubbleSort(ListaSeq *L) {
    MET_START;
    int n = L->tamanho;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            C++;
            if (L->itens[j].rg > L->itens[j + 1].rg) {
                Item tmp = L->itens[j];
                L->itens[j] = L->itens[j + 1];
                L->itens[j + 1] = tmp;
                M += 3;
            }
        }
    }
    MET_END("bubbleSort");
}

// Shell Sort
void shellSort(ListaSeq *L) {
    MET_START;
    int n = L->tamanho;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            Item tmp = L->itens[i]; M++;
            int j = i;
            while (j >= gap) {
                C++;
                if (L->itens[j - gap].rg > tmp.rg) {
                    L->itens[j] = L->itens[j - gap]; M++;
                    j -= gap;
                } else {
                    break;
                }
            }
            L->itens[j] = tmp; M++;
        }
    }
    MET_END("shellSort");
}

// Quick Sort helpers
static int partition(Item *A, int low, int high, long *C, long *M) {
    Item pivot = A[high]; (*M)++;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        (*C)++;
        if (A[j].rg <= pivot.rg) {
            ++i;
            Item tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
            (*M) += 3;
        }
    }
    Item tmp = A[i + 1];
    A[i + 1] = A[high];
    A[high] = tmp;
    (*M) += 3;
    return i + 1;
}
static void quickSortRec(Item *A, int low, int high, long *C, long *M) {
    if (low < high) {
        int pi = partition(A, low, high, C, M);
        quickSortRec(A, low, pi - 1, C, M);
        quickSortRec(A, pi + 1, high, C, M);
    }
}
void quickSort(ListaSeq *L) {
    MET_START;
    quickSortRec(L->itens, 0, L->tamanho - 1, &C, &M);
    MET_END("quickSort");
}

// Merge Sort helpers
static void merge(Item *A, int l, int m, int r, long *C, long *M) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Item *L1 = malloc(sizeof(Item) * n1);
    Item *L2 = malloc(sizeof(Item) * n2);
    for (int i = 0; i < n1; ++i) {
        L1[i] = A[l + i];
        (*M)++;
    }
    for (int j = 0; j < n2; ++j) {
        L2[j] = A[m + 1 + j];
        (*M)++;
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        (*C)++;
        if (L1[i].rg <= L2[j].rg) {
            A[k++] = L1[i++];
            (*M)++;
        } else {
            A[k++] = L2[j++];
            (*M)++;
        }
    }
    while (i < n1) {
        A[k++] = L1[i++];
        (*M)++;
    }
    while (j < n2) {
        A[k++] = L2[j++];
        (*M)++;
    }
    free(L1);
    free(L2);
}
static void mergeSortRec(Item *A, int l, int r, long *C, long *M) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortRec(A, l, m, C, M);
        mergeSortRec(A, m + 1, r, C, M);
        merge(A, l, m, r, C, M);
    }
}
void mergeSort(ListaSeq *L) {
    MET_START;
    mergeSortRec(L->itens, 0, L->tamanho - 1, &C, &M);
    MET_END("mergeSort");
}

// I/O e exibição
void imprimirListaSeq(ListaSeq *L) {
    for (int i = 0; i < L->tamanho; ++i) {
        printf("%s,%d\n", L->itens[i].nome, L->itens[i].rg);
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
    char nome[MAX_NOME];
    int rg;
    while (fscanf(f, " %49[^,],%d", nome, &rg) == 2) {
        inserirFimSeq(L, nome, rg);
    }
    fclose(f);
}
