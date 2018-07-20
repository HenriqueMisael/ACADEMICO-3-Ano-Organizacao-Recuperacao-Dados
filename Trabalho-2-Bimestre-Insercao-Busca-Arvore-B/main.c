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
    if(paginaRaiz== 0) {
        println("Nao existe raiz. Insira pelo menos uma chave para listar a arvore.");
    } else {
        listar_arvore();
    }
}

void busca() {
    printf("busca\n");
}

void insercao() {
    println("Digite a chave para inserir:");
    insere(readInt());
}

void insere(CHAVE chave) {
    paginaRaiz = inserir(chave, paginaRaiz);
}

void importacao() {
    novo_arquivo();
    fecha_arquivo();
    le_raiz_arquivo(&paginaRaiz);
    println("Novo arquivo gerado.");
}
