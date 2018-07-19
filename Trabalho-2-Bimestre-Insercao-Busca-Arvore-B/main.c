#include <malloc.h>
#include <memory.h>
#include <stdbool.h>

#include "main.h"

RRN paginaRaiz;

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
    listar_arvore();
}

void busca() {
    printf("busca\n");
}

void insercao() {
    insere(100);
    insere(50);
    insere(150);
    insere(40);
}

void insere(CHAVE chave) {
    paginaRaiz = inserir(chave, paginaRaiz);
}

void importacao() {
    printf("importacao\n");
}
