#ifndef LIB_ENC_H
#define LIB_ENC_H

#define MAX_NOME 50

typedef struct Node {
    char nome[MAX_NOME];
    int  rg;
    struct Node *proximo;
} Node;

// criação/liberação
Node* criarListaEnc(void);
void  liberarListaEnc(Node *head);

// inserções
void inserirInicioEnc   (Node **head, const char *nome, int rg);
void inserirFimEnc      (Node **head, const char *nome, int rg);
void inserirPosicaoEnc  (Node **head, const char *nome, int rg, int pos);

// remoções
void removerInicioEnc   (Node **head);
void removerFimEnc      (Node **head);
void removerPosicaoEnc  (Node **head, int pos);

// busca
void buscarEnc          (Node *head, int rg);

// I/O e exibição
void imprimirListaEnc   (Node *head);
void gravarArquivoEnc   (Node *head, const char *nomeArquivo);
Node* lerArquivoEnc     (const char *nomeArquivo);

// menu
void menuEncadeada      (Node **head);

#endif // LIB_ENC_H
