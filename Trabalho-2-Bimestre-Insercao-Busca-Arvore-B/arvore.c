#include <memory.h>
#include <malloc.h>
#include "util.h"
#include "arvore.h"

FILE *file;

void cabecalho_arquivo(RRN raiz) {
    fwrite(&raiz, sizeof(RRN), 1, file);
}

void verifica_cria_arquivo() {
    if (!abre_arquivo()) {
        file = fopen(NOME_ARQUIVO, "wb");
        cabecalho_arquivo(0);
    }
    fecha_arquivo();
}

void le_raiz_arquivo(RRN *raiz) {
    abre_arquivo();
    fread(raiz, sizeof(RRN), 1, file);
    fecha_arquivo();
}

int abre_arquivo() {

    file = fopen(NOME_ARQUIVO, "rb+");

    return file != NULL;
}

void fecha_arquivo() {
    fclose(file);
}

void posiciona_arquivo(RRN rrn) {
    fseek(file, sizeof(RRN) + ((rrn - 1) * sizeof(PAGINA)), SEEK_SET);
}

PAGINA lerPagina_arquivo(RRN rrn) {
    PAGINA result;

    abre_arquivo();
    posiciona_arquivo(rrn);
    fread(&result, sizeof(PAGINA), 1, file);
    fecha_arquivo();

    return result;
}

PAGINA *criaNovaPagina() {
    PAGINA *nova = (PAGINA *) malloc(sizeof(PAGINA));
    int i;

    nova->lotacao = 0;
    for (i = 0; i < ORDEM; i++) {
        nova->filhos[i] = EMPTY_RRN;
    }

    return nova;
}

PAGINA_AUXILIAR *criaNovaPaginaAuxiliar(PAGINA pagina) {
    PAGINA_AUXILIAR *nova = (PAGINA_AUXILIAR *) malloc(sizeof(PAGINA_AUXILIAR));
    int i;

    nova->lotacao = pagina.lotacao;
    for (i = 0; i < ORDEM; i++) {
        nova->filhos[i] = pagina.filhos[i];
        strcpy(nova->chaves[i], pagina.chaves[i]);
    }

    return nova;
}

int comparaChaves(CHAVE primeira, CHAVE segunda) {
    return strcmp(primeira, segunda);
}

int busca_arvore(RRN rrn, CHAVE chave, RRN *rrn_encontrado, int *posicao_encontrada) {

    if (rrn == EMPTY_RRN) {
        return FALSE;
    }

    PAGINA pagina = lerPagina_arquivo(rrn);
    int i;
    for (i = 0; i < LOTACAO_MAX; i++) {
        int comparacao = comparaChaves(pagina.chaves[i], chave);
        if (comparacao == 0) {
            *rrn_encontrado = rrn;
            *posicao_encontrada = i;
            return TRUE;
        } else if (comparacao > 0) {
            return busca_arvore(pagina.filhos[i], chave, rrn_encontrado, posicao_encontrada);
        }
    }
    return FALSE;
}

int insere_pagina(PAGINA *pagina, RRN rrn, CHAVE chave) {
    int i;

    for (i = pagina->lotacao; comparaChaves(pagina->chaves[i - 1], chave) > 0 && i > 0; i--) {
        strcpy(pagina->chaves[i], pagina->chaves[i - 1]);
        pagina->filhos[i + 1] = pagina->filhos[i];
    }

    pagina->lotacao++;
    strcpy(pagina->chaves[i], chave);
    pagina->filhos[i + 1] = rrn;
}

int insere_pagina_auxiliar(PAGINA_AUXILIAR *pagina, RRN rrn, CHAVE chave) {
    int i;

    for (i = pagina->lotacao; comparaChaves(pagina->chaves[i - 1], chave) > 0 && i > 0; i--) {
        strcpy(pagina->chaves[i], pagina->chaves[i - 1]);
        pagina->filhos[i + 1] = pagina->filhos[i];
    }

    pagina->lotacao++;
    strcpy(pagina->chaves[i], chave);
    pagina->filhos[i + 1] = rrn;
}

int insere_arvore(RRN rrnAtual, CHAVE chaveInserir, RRN *rrnPromocao, CHAVE *chavePromocao) {
    PAGINA *paginaAtual = criaNovaPagina();
    PAGINA *novaPagina = criaNovaPagina();
    CHAVE *chavePromocaoAtual = (CHAVE *) malloc(sizeof(CHAVE));
    RRN *rrnPromocaoAtual = (RRN *) malloc(sizeof(RRN));
    int i;

    if (rrnAtual == EMPTY_RRN) {
        strcpy(*chavePromocaoAtual, chaveInserir);
        *rrnPromocaoAtual = EMPTY_RRN;
        return INSERCAO_PROMOCAO;
    }

    *paginaAtual = lerPagina_arquivo(rrnAtual);
    for (i = 0; i < LOTACAO_MAX; i++) {
        int comparacao = comparaChaves(paginaAtual->chaves[i], chaveInserir);
        if (comparacao == 0) {
            return INSERCAO_ERRO;
        } else if (comparacao > 1) {
            break;
        }
    }

    int retorno = insere_arvore(paginaAtual->filhos[i], chaveInserir, rrnPromocaoAtual, chavePromocaoAtual);
    if (retorno == INSERCAO_SEM_PROMOCAO || retorno == INSERCAO_ERRO) {
        return retorno;
    }

    if (paginaAtual->lotacao < LOTACAO_MAX) {
        insere_pagina(paginaAtual, *rrnPromocaoAtual, *chavePromocaoAtual);
        escreve_arquivo(paginaAtual, rrnAtual);
        return INSERCAO_SEM_PROMOCAO;
    }

    divide_pagina(*chavePromocaoAtual, *rrnPromocaoAtual, paginaAtual, chavePromocao, rrnPromocao, novaPagina);
    escreve_arquivo(paginaAtual, rrnAtual);
    escreve_arquivo(novaPagina, *rrnPromocao);
    return INSERCAO_PROMOCAO;
}

void divide_pagina(CHAVE chavePromocaoAtual, RRN rrnPromocaoAtual, PAGINA *paginaAtual, CHAVE *chavePromocao,
                   RRN *rrnPromocao, PAGINA *novaPagina) {
    PAGINA_AUXILIAR *pagina_auxiliar = criaNovaPaginaAuxiliar(*paginaAtual);
    insere_pagina_auxiliar(pagina_auxiliar, rrnPromocaoAtual, chavePromocaoAtual);
    novaPagina = criaNovaPagina();
    chavePromocao = mediana_pagina(pagina_auxiliar);
    *rrnPromocao = novo_rrn();

    int i;

    for (i = 0; comparaChaves(pagina_auxiliar->chaves[i], *chavePromocao) < 0; i++) {
        strcpy(paginaAtual->chaves[i], pagina_auxiliar->chaves[i]);
    }
    for (; i < pagina_auxiliar->lotacao; i++) {
        strcpy(novaPagina->chaves[i], pagina_auxiliar->chaves[i]);
    }
}

RRN novo_rrn() {
    abre_arquivo();
    fseek(file, 0, SEEK_END);

    long tamanhoArquivo = ftell(file);
    size_t tamanhoRRN = sizeof(RRN);
    size_t tamanhoPAGINA = sizeof(PAGINA);

    int novoRRN = (tamanhoArquivo - tamanhoRRN) / tamanhoPAGINA + 1;

    fecha_arquivo();
    return novoRRN;
}

CHAVE *mediana_pagina(PAGINA_AUXILIAR *auxiliar) {

    int posicao = auxiliar->lotacao / 2;
    CHAVE *mediana = (CHAVE *) malloc(sizeof(CHAVE));
    strcpy(*mediana, auxiliar->chaves[posicao]);

    return mediana;
}

void escreve_arquivo(PAGINA *atual, RRN rrnAtual) {
    abre_arquivo();
    posiciona_arquivo(rrnAtual);
    fwrite(atual, sizeof(PAGINA), 1, file);
    fecha_arquivo();
}

RRN inserir(CHAVE chave, RRN raiz) {
    RRN rrnPromocao = EMPTY_RRN;
    CHAVE chavePromocao;
    CHAVE chaveInserir;
    int i, j;

    j = strlen(chave) - 1;
    for (i = sizeof(CHAVE) - 1; j >= 0; i--, j--) {
        chaveInserir[i] = chave[j];
    }

    while (i >= 0) {
        chaveInserir[i--] = '0';
    }

    switch (insere_arvore(raiz, chaveInserir, &rrnPromocao, &chavePromocao)) {
        case INSERCAO_ERRO:
            println("Erro ao inserir: chave repetida");
            break;
        case INSERCAO_PROMOCAO:
            raiz = geraNovaRaiz(chave, raiz, rrnPromocao);
            println("Nova raiz gerada.");
        case INSERCAO_SEM_PROMOCAO:
            println("Chave inserida com sucesso");
            break;
    }

    return raiz;
}

RRN geraNovaRaiz(CHAVE chave, RRN esquerda, RRN direita) {
    PAGINA *pagina = criaNovaPagina();
    RRN rrn = novo_rrn();

    strcpy(pagina->chaves[0], chave);
    pagina->filhos[0] = esquerda;
    pagina->filhos[1] = direita;
    pagina->lotacao = 1;

    cabecalho_arquivo(rrn);
    escreve_arquivo(pagina, rrn);
    return rrn;
}
