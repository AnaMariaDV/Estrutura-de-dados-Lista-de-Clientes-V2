#include <stdio.h>
#include "lib_seq.h"
#include "lib_enc.h"

int main() {
    ListaSeq seq;
    Node *enc = NULL;
    int opt;
    printf("\nEscolha uma das opcoes abaixo:\n");
    printf("1) Sequencial\n2) Encadeada\n>> ");
    scanf("%d", &opt);

    if (opt == 1) {
        criarListaSeq(&seq);
        menuSequencial(&seq);
        liberarListaSeq(&seq);
    } else {
        enc = criarListaEnc();
        menuEncadeada(&enc);
        liberarListaEnc(enc);
    }
    return 0;
}
