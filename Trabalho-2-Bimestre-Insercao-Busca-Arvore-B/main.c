#include <malloc.h>
#include <memory.h>
#include <zconf.h>
#include <stdbool.h>

#include "main.h"
#include "menu.h"
#include "util.h"

int main() {

    Menu *mainMenu;
    mainMenu = newMenu(5, newItemMenu("Sair", &fechar), newItemMenu("Importacao", &importacao),
                       newItemMenu("Insercao", &insercao), newItemMenu("Busca", &busca),
                       newItemMenu("Listagem", &listagem));

    fecharPrograma = FALSE;

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
    printf("insercao\n");
}

void importacao() {
    printf("importacao\n");
}