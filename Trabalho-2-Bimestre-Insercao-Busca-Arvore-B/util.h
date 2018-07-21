#ifndef TRABALHO_2_BIMESTRE_INSERCAO_BUSCA_ARVORE_B_UTIL_H
#define TRABALHO_2_BIMESTRE_INSERCAO_BUSCA_ARVORE_B_UTIL_H

#include <stdio.h>
#include <memory.h>
#include <malloc.h>

static const int FALSE = 0;
static const int TRUE = 1;

int readInt();

char *readString(int tamanho);

int pede_arquivo(FILE **arquivo);

void println(const char *text);

#endif //TRABALHO_2_BIMESTRE_INSERCAO_BUSCA_ARVORE_B_UTIL_H