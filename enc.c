#include "lib_enc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Node* criarListaEnc(void) {
    return NULL;
}

void liberarListaEnc(Node *head) {
    while (head) {
        Node *t = head;
        head = head->proximo;
        free(t);
    }
}

#define MET_START  clock_t _t0 = clock(); long C=0, M=0;
#define MET_END(msg) \
    printf(msg " ⇒ C(n)=%ld, M(n)=%ld, tempo=%.6fs\n", \
           C, M, (double)(clock()-_t0)/CLOCKS_PER_SEC)

void inserirInicioEnc(Node **head, const char *nome, int rg) {
    MET_START;
    Node *n = malloc(sizeof(Node));
    strncpy(n->nome, nome, MAX_NOME);
    n->rg = rg; M++;
    n->proximo = *head; M++;
    *head = n;
    printf("Inserido: %s, %d, posição: 0\n", n->nome, n->rg);
    MET_END("inserirInicioEnc");
}

void inserirFimEnc(Node **head, const char *nome, int rg) {
    MET_START;
    Node *n = malloc(sizeof(Node));
    strncpy(n->nome, nome, MAX_NOME);
    n->rg = rg; M++;
    n->proximo = NULL;
    int pos = 0;
    if (!*head) {
        *head = n; M++;
        printf("Inserido: %s, %d, posição: %d\n", n->nome, n->rg, pos);
        MET_END("inserirFimEnc");
        return;
    }
    Node *p = *head;
    while (p->proximo) { p = p->proximo; C++; pos++; }
    p->proximo = n; M++;
    printf("Inserido: %s, %d, posição: %d\n", n->nome, n->rg, pos + 1);
    MET_END("inserirFimEnc");
}

void inserirPosicaoEnc(Node **head, const char *nome, int rg, int pos) {
    if (pos == 0) {
        inserirInicioEnc(head, nome, rg);
        return;
    }
    MET_START;
    Node *p = *head; int i = 0;
    while (p && i + 1 < pos) { p = p->proximo; C++; i++; }
    Node *n = malloc(sizeof(Node));
    strncpy(n->nome, nome, MAX_NOME);
    n->rg = rg; M++;
    n->proximo = p ? p->proximo : NULL; M++;
    if (p) p->proximo = n; else *head = n;
    printf("Inserido: %s, %d, posição: %d\n", n->nome, n->rg, pos);
    MET_END("inserirPosicaoEnc");
}

void removerInicioEnc(Node **head) {
    MET_START;
    if (!*head) return;
    Node *t = *head;
    printf("Removido: %s, %d, posição: 0\n", t->nome, t->rg);
    *head = t->proximo; M++;
    free(t);
    MET_END("removerInicioEnc");
}

void removerFimEnc(Node **head) {
    MET_START;
    if (!*head) return;
    Node *p = *head, *ant = NULL;
    int pos = 0;
    while (p->proximo) { ant = p; p = p->proximo; C++; pos++; }
    printf("Removido: %s, %d, posição: %d\n", p->nome, p->rg, pos);
    if (ant) ant->proximo = NULL, M++;
    else    *head = NULL;
    free(p);
    MET_END("removerFimEnc");
}

void removerPosicaoEnc(Node **head, int pos) {
    if (pos == 0) {
        removerInicioEnc(head);
        return;
    }
    MET_START;
    Node *p = *head, *ant = NULL; int i = 0;
    while (p && i < pos) { ant = p; p = p->proximo; C++; i++; }
    if (!p) return;
    printf("Removido: %s, %d, posição: %d\n", p->nome, p->rg, pos);
    ant->proximo = p->proximo; M++;
    free(p);
    MET_END("removerPosicaoEnc");
}

void buscarEnc(Node *head, int rg) {
    MET_START;
    int pos = 0;
    while (head) {
        C++;
        if (head->rg == rg) {
            printf("Encontrado: %s, %d, posição: %d\n", head->nome, head->rg, pos);
            MET_END("buscarEnc");
            return;
        }
        head = head->proximo;
        pos++;
    }
    printf("buscarEnc: não encontrado\n");
}

void imprimirListaEnc(Node *head) {
    int pos = 0;
    while (head) {
        printf("%d: %s,%d\n", pos, head->nome, head->rg);
        head = head->proximo;
        pos++;
    }
}

void gravarArquivoEnc(Node *head, const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "w");
    while (head) {
        fprintf(f, "%s,%d\n", head->nome, head->rg);
        head = head->proximo;
    }
    fclose(f);
}

Node* lerArquivoEnc(const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (!f) return NULL;
    Node *head = criarListaEnc();
    char linha[128], nome[MAX_NOME];
    int rg;
    while (fgets(linha, sizeof(linha), f)) {
        if (sscanf(linha, " %49[^,],%d", nome, &rg) == 2) {
            inserirFimEnc(&head, nome, rg);
        }
    }
    fclose(f);
    return head;
}
