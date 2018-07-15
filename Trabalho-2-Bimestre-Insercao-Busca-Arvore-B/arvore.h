#ifndef TRABALHO_2_BIMESTRE_INSERCAO_BUSCA_ARVORE_B_BUSCA_H
#define TRABALHO_2_BIMESTRE_INSERCAO_BUSCA_ARVORE_B_BUSCA_H

#define ORDEM 5
#define LOTACAO_MAX ORDEM-1

#define INSERCAO_ERRO  0
#define INSERCAO_PROMOCAO  1
#define INSERCAO_SEM_PROMOCAO 2

#define EMPTY_RRN 0

typedef char CHAVE[6];
typedef long RRN;

typedef struct {
    CHAVE chaves[LOTACAO_MAX];
    RRN filhos[ORDEM];
    int lotacao;
} PAGINA;

typedef struct {
    CHAVE chaves[LOTACAO_MAX + 1];
    RRN filhos[ORDEM + 1];
    int lotacao;
} PAGINA_AUXILIAR;

static char *const NOME_ARQUIVO = "indice";

void verifica_cria_arquivo();

void le_raiz_arquivo(RRN *raiz);

PAGINA lerPagina_arquivo(RRN rrn);

void posiciona_arquivo(RRN rrn);

void escreve_arquivo(PAGINA *atual, RRN rrnAtual);

int abre_arquivo();

void fecha_arquivo();

CHAVE *mediana_pagina(PAGINA_AUXILIAR *auxiliar);

int comparaChaves(CHAVE i, CHAVE chave);

int busca_arvore(RRN rrn, CHAVE chave, RRN *rrn_encontrado, int *posicao_encontrada);

int insere_arvore(RRN rrnAtual, CHAVE chaveInserir, RRN *rrnPromocao, CHAVE *chavePromocao);

void divide_pagina(CHAVE chavePromocaoAtual, RRN rrnPromocaoAtual, PAGINA *paginaAtual, CHAVE *chavePromocao,
                   RRN *rrnPromocao, PAGINA *novaPagina);

RRN novo_rrn();

RRN inserir(CHAVE chave, RRN raiz);

int insere_pagina(PAGINA *pagina, RRN rrn, CHAVE chave);

int insere_pagina_auxiliar(PAGINA_AUXILIAR *pagina, RRN rrn, CHAVE chave);

RRN geraNovaRaiz(CHAVE chave, RRN esquerda, RRN direita);

#endif //TRABALHO_2_BIMESTRE_INSERCAO_BUSCA_ARVORE_B_BUSCA_H
