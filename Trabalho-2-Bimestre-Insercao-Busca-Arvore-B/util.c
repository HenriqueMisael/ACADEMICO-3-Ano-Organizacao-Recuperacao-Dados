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