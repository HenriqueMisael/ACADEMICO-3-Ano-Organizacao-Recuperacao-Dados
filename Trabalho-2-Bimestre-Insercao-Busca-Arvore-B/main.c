#include <malloc.h>
#include <memory.h>
#include <stdbool.h>

#include "main.h"
#include "menu.h"
#include "util.h"
#include "arvore.h"

RRN paginaRaiz;

void insere(char string[4]);

int main() {

    Menu *mainMenu;
    mainMenu = newMenu(5, newItemMenu("Sair", &fechar), newItemMenu("Importacao", &importacao),
                       newItemMenu("Insercao", &insercao), newItemMenu("Busca", &busca),
                       newItemMenu("Listagem", &listagem));

    fecharPrograma = FALSE;
    verifica_cria_arquivo();
    le_raiz_arquivo(&paginaRaiz);

    do {
        executaMenu(mainMenu);
    } while (!fecharPrograma);

    return 0;
}

void fechar() {
    fecharPrograma = TRUE;
}

void listagem() {
    printf("listagem\n");
}

void busca() {
    printf("busca\n");
}

void insercao() {
    insere("100");
    insere("50");
    insere("150");
    insere("40");
    insere("30");
    insere("70");
    insere("60");
    insere("55");
    insere("90");
    insere("91");
    insere("89");
}

void insere(CHAVE chave) {
    paginaRaiz = inserir(chave, paginaRaiz);
}

void importacao() {
    printf("importacao\n");
}
