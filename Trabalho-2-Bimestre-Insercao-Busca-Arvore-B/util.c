#include "util.h"

int readInt() {
    int readed;

    scanf("%d", &readed);

    return readed;
}

char *readString(int tamanho) {
    char *readed = (char *) malloc(tamanho);

    fscanf(stdin, "%s", readed);

    for(int i = 0; i < tamanho; i++) {
        char c = readed[i];
        if(c == '\n') {
            readed[i] = '\0';
            break;
        }
    }

    return readed;
}

void println(const char *text) {
    printf("%s\n", text);
}

int pede_arquivo(FILE ** arquivo) {
    println("Digite um nome de arquivo (ate 40 caracteres) para validar importacao:");
    *arquivo = fopen(readString(40), "r");

    if (*arquivo == NULL) {
        println("Arquivo nao encontrado.");
        return FALSE;
    }
    return TRUE;
}