#include "TFile.h"

#define NOME_ARQUIVO "registros.dat"

FILE* file;
long offsetLedAnterior;
char* delecao = "*|";

void escreveNoLed(long cabecaLed) {
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

void escrevePosicao() {
    printf("%ld\n", ftell(file));
}
void TFile_append(TCandidato* c){
    int tamanho;
    int offSetGravacao;
    char* buffer = TCandidato_toString(c);
    long proximoOffsetLed;
    int consumiuLed;
    
    tamanho = strlen(buffer);
    file = openFileToUse();
    
    consumiuLed = achaEspacoDisponivel(tamanho, &proximoOffsetLed);
    gravaNovoRegistro(buffer, tamanho);
    
    if(consumiuLed) {
        fseek(file, offsetLedAnterior, SEEK_SET);
        escreveNoLed(proximoOffsetLed);
    }
    
    fclose(file);
}

int posiciona(char* inscricao) {
    TFile_avancaNoLed();
    while(!feof(file)) {
        short tamanho;
        if(fread(&tamanho, sizeof(tamanho), 1, file) == 0) {
            break;
        }
        
        char* buffer = (char*)malloc(tamanho);
        tamanho = fread(buffer, 1, tamanho, file);
        buffer[tamanho] = '\0';
        short resultado = strcmp(strtok(buffer, "|"), inscricao);
        
        free(buffer);
        
        if(!resultado) {
            fseek(file, -(sizeof(tamanho) + tamanho), SEEK_CUR);
            return tamanho;
        }
    }
    
    return 0;
}

void posicionaFimLed() {
    TFile_posicionaInicio();
    
    while(1) {
        long novoOffset;
        fread(&novoOffset, sizeof(novoOffset), 1, file);
        if(novoOffset == -1){
            TFile_retornaNoLed();
            break;
        }
        fseek(file, novoOffset, SEEK_SET);
        TFile_avancaTamanho();
        TFile_avancaMarcadorDelecao();
    }
}

int achaEspacoDisponivel(short tamanho, long* proximoOffsetLed) {
    long novoOffset;
    short espacoLivre;
    
    TFile_posicionaInicio();
    fread(&novoOffset, sizeof(novoOffset), 1, file);
    
    while(!feof(file)) {
        if(novoOffset == -1) {
            TFile_posicionaFim();
            return 0;
        }
        
        fseek(file, novoOffset, SEEK_SET);
        fread(&espacoLivre, sizeof(espacoLivre), 1, file);
        
        if(espacoLivre >= tamanho) {
            TFile_avancaMarcadorDelecao();
            fread(proximoOffsetLed, sizeof(*proximoOffsetLed), 1, file);
            TFile_retornaMarcadorDelecao();
            TFile_retornaNoLed();
            TFile_retornaTamanho();
            break;
        }
        TFile_avancaMarcadorDelecao();
        offsetLedAnterior = novoOffset;
        fread(&novoOffset, sizeof(novoOffset), 1, file);
    }
    
    return 1;
}

void gravaDelecao() {
    TFile_avancaTamanho();
    fprintf(file, "%s", delecao);
    escreveNoLed(-1L);
    
    TFile_retornaNoLed();
    TFile_retornaTamanho();
    TFile_retornaMarcadorDelecao();
    
    long novoNoLed = ftell(file);
    posicionaFimLed();
    escreveNoLed(novoNoLed);
}

void TFile_remove(char* inscricao){
    file = openFileToUse();
    
    if(posiciona(inscricao)) {
        gravaDelecao();
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
void TFile_showContent() {
    file = openFileToUse();
    
    TFile_avancaNoLed();
    while(!feof(file)) {
        short tamanho;
        if(fread(&tamanho, sizeof(tamanho), 1, file) == 0) {
            break;
        }
        
        char* buffer = (char*)malloc(tamanho);
        tamanho = fread(buffer, 1, tamanho, file);
        buffer[tamanho] = '\0';
        
        printf(" %ld: %s\n", ftell(file), buffer);
        
        free(buffer);
    }
    
    fclose(file);
}

void TFile_avancaNoLed() {
    fseek(file, sizeof(long), SEEK_CUR);   
}

void TFile_retornaNoLed() {
    fseek(file, -sizeof(long), SEEK_CUR);   
}

void TFile_posicionaInicio() {
    fseek(file, 0, SEEK_SET);
}

void TFile_posicionaFim() {
    fseek(file, 0, SEEK_END);
}

void TFile_avancaTamanho() {
    fseek(file, sizeof(short), SEEK_CUR);
}

void TFile_retornaTamanho() {
    fseek(file, -sizeof(short), SEEK_CUR);
}

void TFile_retornaMarcadorDelecao() {
    fseek(file, -2, SEEK_CUR);
}

void TFile_avancaMarcadorDelecao() {
    fseek(file, 2, SEEK_CUR);
}
