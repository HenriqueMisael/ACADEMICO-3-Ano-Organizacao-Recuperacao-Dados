#include <malloc.h>
#include <memory.h>
#include <stdbool.h>

#include "main.h"

RRN paginaRaiz;

void resultadoTeste(bool resultado);

int main() {

    Menu *mainMenu;
    mainMenu = newMenu(7, newItemMenu("Sair", &fechar), newItemMenu("Importacao", &importacao),
                       newItemMenu("Insercao", &insercao), newItemMenu("Busca", &busca),
                       newItemMenu("Listagem", &listagem), newItemMenu("Importar e testar", &testaImportacao),
                       newItemMenu("Testar importados", &testaImportacaoApenas));

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

    println("Qual chave deseja buscar?");
    CHAVE chave = readInt();
    buscaChave(chave);
}

void buscaChave(CHAVE chave) {
    RRN rrn;
    int posicao;
    if (busca_arvore(paginaRaiz, chave, &rrn, &posicao)) {
        printf("Chave %d encontrada na pagina %ld, a posicao %d.\n", chave, rrn, posicao);
        PAGINA paginaEncontrada = lerPagina_arquivo(rrn);
        imprimePagina(rrn, paginaEncontrada);
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
    println("A primeira linha do arquivo deve conter quantas chaves serao importadas, e as seguintes os valores.");
    println("Digite um nome de arquivo (ate 40 caracteres) para importar:");
    char *nomeArquivo = readString(40);
    FILE *entrada = fopen(nomeArquivo, "r");

    if (entrada == NULL) {
        println("Arquivo nao encontrado.");
        return;
    }

    importa_arquivo(entrada);
}

void importa_arquivo(FILE *entrada) {
    novo_arquivo();
    fecha_arquivo();

    int quantidadeChaves;
    fscanf(entrada, "%d", &quantidadeChaves);

    while (quantidadeChaves--) {
        CHAVE chave;
        fscanf(entrada, "%d", &chave);

        if (feof(entrada)) {
            break;
        }

        insere(chave);
    }

    le_raiz_arquivo(&paginaRaiz);
    println("Novo arquivo gerado.");
}

void testaImportacao() {
    resultadoTeste(importaTesta());
}

void testaImportacaoApenas() {
    FILE *entrada;
    if (pede_arquivo(&entrada)) {
        bool resultado = buscaChavesArquivo(entrada);
        resultadoTeste(resultado);
    }
}

void resultadoTeste(bool resultado) {
    if (resultado) {
        println("Os algoritmos de insercao e busca estao corretos!");
    } else {
        println("Tem coisa errada ai, cara :/");
    }
}

int importaTesta() {
    FILE *entrada;

    if (!pede_arquivo(&entrada)) {
        return FALSE;
    }

    importa_arquivo(entrada);
    fseek(entrada, 0, SEEK_SET);
    return buscaChavesArquivo(entrada);
}

int buscaChavesArquivo(FILE *entrada) {
    int quantidadeChaves;
    fscanf(entrada, "%d", &quantidadeChaves);

    while (quantidadeChaves--) {
        CHAVE chave;
        fscanf(entrada, "%d", &chave);

        if (feof(entrada)) {
            break;
        }

        RRN rrn;
        int posicao;
        if (!busca_arvore(paginaRaiz, chave, &rrn, &posicao)) {
            return FALSE;
        } else {
            printf("Chave %d encontrada!\n", chave);
        }
    }
    return TRUE;
}