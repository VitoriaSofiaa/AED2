#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

int main() {
    int N = 8, dados[8] = {50, 100, 30, 20, 40, 45, 35, 37};
    ArvBin* raiz = cria_ArvBin();

    for (int i = 0; i < N; i++) {
        insere_ArvBin(raiz, dados[i]);
        printf("Tamanho atual: %d\n", totalNO_ArvBin(raiz));
    }

    printf("\nPré-Ordem antes da remoção: ");
    preOrdem_ArvBin(raiz);
    printf("\n");

    // Testando remoção
    if (remove_ArvBin(raiz, 50)) {
        printf("\nRemovido com sucesso!\n");
    } else {
        printf("\nNão encontrado!\n");
    }

    printf("Pré-Ordem após remoção: ");
    preOrdem_ArvBin(raiz);
    printf("\n");

    libera_ArvBin(raiz);
    printf("\nFim!\n");
    return 0;
}
