#ifndef LIB_SEQ_H
#define LIB_SEQ_H

#define MAX_NOME 50

typedef struct {
    char nome[MAX_NOME];
    int  rg;
} Item;

typedef struct {
    Item *itens;
    int   tamanho;
    int   capacidade;
} ListaSeq;

// gerenciamento de memória
void criarListaSeq  (ListaSeq *L);
void liberarListaSeq(ListaSeq *L);

// inserções
void inserirInicioSeq  (ListaSeq *L, const char *nome, int rg);
void inserirFimSeq     (ListaSeq *L, const char *nome, int rg);
void inserirPosicaoSeq (ListaSeq *L, const char *nome, int rg, int pos);

// remoções
void removerInicioSeq  (ListaSeq *L);
void removerFimSeq     (ListaSeq *L);
void removerPosicaoSeq (ListaSeq *L, int pos);

// buscas
void buscarSeq     (ListaSeq *L, int rg);
void buscarBinSeq  (ListaSeq *L, int rg);

// ordenações
void selectionSort  (ListaSeq *L);
void insertionSort  (ListaSeq *L);
void bubbleSort     (ListaSeq *L);
void shellSort      (ListaSeq *L);
void quickSort      (ListaSeq *L);
void mergeSort      (ListaSeq *L);

// I/O e exibição
void imprimirListaSeq   (ListaSeq *L);
void gravarArquivoSeq   (ListaSeq *L, const char *nomeArquivo);
void lerArquivoSeq      (ListaSeq *L, const char *nomeArquivo);

// menu interativo
void menuSequencial     (ListaSeq *L);

#endif // LIB_SEQ_H
