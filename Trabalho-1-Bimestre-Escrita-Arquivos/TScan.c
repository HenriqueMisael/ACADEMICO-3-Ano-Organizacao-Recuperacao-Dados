#include "TScan.h"

char* TScan_get(char* enunciado, int tamanho) {
    char* buffer = (char*)malloc(sizeof(char)*tamanho);
    int i;
    
    printf(enunciado);
    fgets(buffer, tamanho, stdin);
    
    for(i = 0; i < tamanho; i++){
        if(buffer[i] == '\n') {
           buffer[i] = '\0';
           break;
       }
    }

    return buffer;
}

long TScan_getLong(char* enunciado) {
    long readed;
    
    printf(enunciado);
    scanf("%ld", &readed);
    getchar();
    
    return readed;
}

double TScan_getDouble(char* enunciado) {
    double readed;
    
    printf(enunciado);
    scanf("%lf", &readed);
    getchar();
    
    return readed;
}
