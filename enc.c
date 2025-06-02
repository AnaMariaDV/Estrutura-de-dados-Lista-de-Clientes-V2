// enc.c — Implementação da Lista Encadeada (sem menu)
#include "lib_enc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>;
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
#define MET_END(msg,pos) \
    printf(msg " ⇒ C(n)=%ld, M(n)=%ld, tempo=%.6fs, pos=%d\n", \
           C, M, (double)(clock()-_t0)/CLOCKS_PER_SEC, pos);

void inserirInicioEnc(Node **head, const char *nome, int rg) {
    MET_START;
    Node *n = malloc(sizeof(Node));
    strncpy(n->nome, nome, MAX_NOME);
    n->rg = rg; M++;
    n->proximo = *head; M++;
    *head = n;
    MET_END("inserirInicioEnc", 0);
}

void inserirFimEnc(Node **head, const char *nome, int rg) {
    MET_START;
    Node *n = malloc(sizeof(Node));
    strncpy(n->nome, nome, MAX_NOME);
    n->rg = rg; M++;
    n->proximo = NULL;
    if (!*head) {
        *head = n; M++;
        MET_END("inserirFimEnc", 0);
        return;
    }
    Node *p = *head; int pos = 0;
    while (p->proximo) { p = p->proximo; C++; pos++; }
    p->proximo = n; M++;
    MET_END("inserirFimEnc", pos+1);
}

void inserirPosicaoEnc(Node **head, const char *nome, int rg, int pos) {
    if (pos == 0) {
        inserirInicioEnc(head, nome, rg);
        return;
    }
    MET_START;
    Node *p = *head; int i = 0;
    while (p && i+1 < pos) { p = p->proximo; C++; i++; }
    Node *n = malloc(sizeof(Node));
    strncpy(n->nome, nome, MAX_NOME);
    n->rg = rg; M++;
    n->proximo = p ? p->proximo : NULL; M++;
    if (p) p->proximo = n; else *head = n;
    MET_END("inserirPosicaoEnc", pos);
}

void removerInicioEnc(Node **head) {
    MET_START;
    if (!*head) return;
    Node *t = *head;
    *head = t->proximo; M++;
    free(t);
    MET_END("removerInicioEnc", 0);
}

void removerFimEnc(Node **head) {
    MET_START;
    if (!*head) return;
    Node *p = *head, *ant = NULL; int pos = 0;
    while (p->proximo) { ant = p; p = p->proximo; C++; pos++; }
    if (ant) ant->proximo = NULL, M++;
    else    *head = NULL;
    free(p);
    MET_END("removerFimEnc", pos);
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
    ant->proximo = p->proximo; M++;
    free(p);
    MET_END("removerPosicaoEnc", pos);
}

void buscarEnc(Node *head, int rg) {
    MET_START;
    int pos = 0;
    while (head) {
        C++;
        if (head->rg == rg) {
            MET_END("buscarEnc", pos);
            return;
        }
        head = head->proximo; pos++;
    }
    puts("buscarEnc: nao encontrado");
}

void imprimirListaEnc(Node *head) {
    while (head) {
        printf("%s,%d\n", head->nome, head->rg);
        head = head->proximo;
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
    char nome[MAX_NOME];
    int rg;
    while (fscanf(f, " %49[^,],%d", nome, &rg) == 2)
        inserirFimEnc(&head, nome, rg);
    fclose(f);
    return head;
}
