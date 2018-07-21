#ifndef TRABALHO_2_BIMESTRE_INSERCAO_BUSCA_ARVORE_B_MAIN_H
#define TRABALHO_2_BIMESTRE_INSERCAO_BUSCA_ARVORE_B_MAIN_H

#include "menu.h"
#include "util.h"
#include "arvore.h"

bool fecharPrograma;

void fechar();

void importacao();

void insercao();

void insere(CHAVE chave);

void busca();

void listagem();

void testaImportacao();

void testaImportacaoApenas();

void importa_arquivo(FILE *entrada);

void buscaChave(CHAVE chave);

int buscaChavesArquivo(FILE *entrada);

int importaTesta();

#endif //TRABALHO_2_BIMESTRE_INSERCAO_BUSCA_ARVORE_B_MAIN_H
