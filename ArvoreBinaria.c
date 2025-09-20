#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

struct NO {
    int info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin() {
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no) {
    if (no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
}

void libera_ArvBin(ArvBin* raiz) {
    if (raiz == NULL)
        return;
    libera_NO(*raiz);
    free(raiz);
}

int insere_ArvBin(ArvBin* raiz, int valor) {
    if (raiz == NULL)
        return 0;
    struct NO* novo = (struct NO*) malloc(sizeof(struct NO));
    if (novo == NULL)
        return 0;
    novo->info = valor;
    novo->esq = novo->dir = NULL;

    if (*raiz == NULL) {
        *raiz = novo;
    } else {
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while (atual != NULL) {
            ant = atual;
            if (valor == atual->info) {
                free(novo);
                return 0; // elemento já existe
            }
            if (valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if (valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

int estaVazia_ArvBin(ArvBin *raiz) {
    if (raiz == NULL) return 1;
    if (*raiz == NULL) return 1;
    return 0;
}

int totalNO_ArvBin(ArvBin *raiz) {
    if (raiz == NULL || *raiz == NULL) return 0;
    return totalNO_ArvBin(&((*raiz)->esq)) +
           totalNO_ArvBin(&((*raiz)->dir)) + 1;
}

int altura_ArvBin(ArvBin *raiz) {
    if (raiz == NULL || *raiz == NULL) return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    return (alt_esq > alt_dir ? alt_esq : alt_dir) + 1;
}

int consulta_ArvBin(ArvBin *raiz, int valor) {
    if (raiz == NULL) return 0;
    struct NO* atual = *raiz;
    while (atual != NULL) {
        if (valor == atual->info)
            return 1;
        if (valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

void preOrdem_ArvBin(ArvBin *raiz) {
    if (raiz == NULL) return;
    if (*raiz != NULL) {
        printf("%d ", (*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void emOrdem_ArvBin(ArvBin *raiz) {
    if (raiz == NULL) return;
    if (*raiz != NULL) {
        emOrdem_ArvBin(&((*raiz)->esq));
        printf("%d ", (*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz) {
    if (raiz == NULL) return;
    if (*raiz != NULL) {
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        printf("%d ", (*raiz)->info);
    }
}

// ===== Funções auxiliares para remoção =====
struct NO* procuraMenor(struct NO* atual) {
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_ArvBin(ArvBin *raiz, int valor) {
    if (raiz == NULL) return 0;

    struct NO* ant = NULL;
    struct NO* atual = *raiz;

    while (atual != NULL && atual->info != valor) {
        ant = atual;
        if (valor < atual->info)
            atual = atual->esq;
        else
            atual = atual->dir;
    }

    if (atual == NULL) return 0; // não encontrado

    // Caso 1 ou 2: 0 ou 1 filho
    if (atual->esq == NULL || atual->dir == NULL) {
        struct NO* temp;
        if (atual->esq != NULL)
            temp = atual->esq;
        else
            temp = atual->dir;

        if (ant == NULL) // removendo a raiz
            *raiz = temp;
        else {
            if (ant->esq == atual)
                ant->esq = temp;
            else
                ant->dir = temp;
        }
        free(atual);
    } else {
        // Caso 3: dois filhos
        struct NO* sucessor = procuraMenor(atual->dir);
        int valorSucessor = sucessor->info;
        remove_ArvBin(&(atual->dir), valorSucessor);
        atual->info = valorSucessor;
    }
    return 1;
}
