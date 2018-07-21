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
    if (paginaRaiz == 0) {
        println("Nao existe raiz. Insira pelo menos uma chave para listar a arvore.");
    } else {
        listar_arvore();
    }
}

void busca() {
    RRN rrn;
    int posicao;

    println("Qual chave deseja buscar?");
    CHAVE chave = readInt();

    if(busca_arvore(paginaRaiz, chave, &rrn, &posicao)) {
        printf("Chave %d encontrada na pagina %ld, a posicao %d.\n", chave, rrn, posicao);
    } else {
        println("Chave nao encontrada!");
    }
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

    println("A primeira linha do arquivo deve conter quantas chaves serao importadas, e as seguintes os valores.");
    println("Digite um nome de arquivo (ate 40 caracteres) para importar:");
    FILE *entrada = fopen(readString(40), "r");

    if(entrada == NULL) {
        println("Arquivo nao encontrado.");
        return;
    }

    int quantidadeChaves;
    fscanf(entrada, "%d", &quantidadeChaves);

    while(quantidadeChaves--) {
        CHAVE chave;
        fscanf(entrada, "%d", &chave);

        if(feof(entrada)) {
            break;
        }

        insere(chave);
    }

    le_raiz_arquivo(&paginaRaiz);
    println("Novo arquivo gerado.");
}
