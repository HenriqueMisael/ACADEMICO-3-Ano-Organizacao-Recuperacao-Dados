#include "TFile.h"

#define NOME_ARQUIVO "registros.dat"

FILE* file;
char* delecao = "*|";

void escreveNoLed(long cabecaLed) {
    printf("Vai escrever LED %ld em %ld\n", cabecaLed, ftell(file));
    fwrite(&cabecaLed, sizeof(cabecaLed), 1, file);
}

void TFile_createNewFile() {
    file = fopen(NOME_ARQUIVO, "w");
    if(file) {
        printf("Arquivo %s criado com sucesso.\n", NOME_ARQUIVO);
        escreveNoLed(-1);
        fclose(file);
        
        printf("Arquivo %s configurado com sucesso.\n", NOME_ARQUIVO);
        
        file = openFileToUse();
        if(!file){
            printf("Nao foi possivel abrir corretamente o arquivo %s..", NOME_ARQUIVO);
        } else {
            fclose(file);
        }
    }
}

void TFile_verify() {
    file = openFileToUse();
    
    if(!file){
        printf("Arquivo %s nao encontrado.\n", NOME_ARQUIVO);
        TFile_createNewFile();
    }
    
    if(file){
        fclose(file);
    }
}

void TFile_append(TCandidato* c){
    int tamanho;
    int offSetGravacao;
    char* buffer = TCandidato_toString(c);
    
    tamanho = strlen(buffer);
    file = openFileToUse();
    
    achaEspacoDisponivel(tamanho);
    gravaNovoRegistro(buffer, tamanho);
    
    fclose(file);
}

int posiciona(char* inscricao) {
    fseek(file, sizeof(long), SEEK_SET);
    char* buffer = (char*)malloc(256);
    
    do {
        short tamanho;
        fread(&tamanho, sizeof(tamanho), 1, file);
        tamanho = fread(buffer, 1, tamanho, file);
        buffer[tamanho] = '\0';
        printf("%s\n", buffer);
        char* current = strtok(buffer, "|");
        if(!strcmp(current, inscricao)){
            return tamanho;
        }
    } while(!feof(file));
    
    return 0;
}

void posicionaInicioRegistro(short tamanho) {
    fseek(file, - (tamanho), SEEK_CUR);
}

void posicionaFimLed() {
    fseek(file, 0, SEEK_SET);
    
    do {
        long novoOffset;
        fread(&novoOffset, sizeof(novoOffset), 1, file);
        if(novoOffset == -1){
            fseek(file, -sizeof(novoOffset), SEEK_CUR);
            break;
        }
        fseek(file, novoOffset, SEEK_SET);
    } while(!feof(file));
}

void achaEspacoDisponivel(short tamanho) {
    fseek(file, 0, SEEK_SET);
    
    do {
        long novoOffset;
        short espacoLivre;
        
        fread(&novoOffset, sizeof(novoOffset), 1, file);
        fseek(file, -(sizeof(delecao) + sizeof(novoOffset)), SEEK_CUR);
        fread(&espacoLivre, sizeof(espacoLivre), 1, file);
        if(novoOffset == -1) {
            fseek(file, 0, SEEK_END);
            break;
        } else if(espacoLivre >= tamanho){
            fseek(file, -sizeof(espacoLivre), SEEK_CUR);
            break;
        }
        
        fseek(file, novoOffset, SEEK_SET);
    } while(!feof(file));
}

void gravaDelecao(tamanho) {
    fprintf(file, "%s", delecao);
    long novoFimLed = ftell(file);
    escreveNoLed(-1L);
    posicionaFimLed();
    escreveNoLed(novoFimLed);
}

void TFile_remove(char* inscricao){
    short tamanho;
    file = openFileToUse();
    
    tamanho = posiciona(inscricao);
    if(tamanho) {
        posicionaInicioRegistro(tamanho);
        gravaDelecao(tamanho);
    } else {
        printf("Nao encontrou inscricao %s para exclusao.\n", inscricao);
    }
    
    fclose(file);
}

void gravaNovoRegistro(char* buffer, short tamanho) {
    fwrite(&tamanho, sizeof(tamanho), 1, file);
    fprintf(file, "%s", buffer);
}

FILE* openFileToUse(){
    return fopen(NOME_ARQUIVO, "r+");
}
