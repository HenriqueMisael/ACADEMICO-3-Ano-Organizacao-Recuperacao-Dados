#include "TCandidato.h"

TCandidato* TCandidato_novo() {
    TCandidato* novo = (TCandidato*)malloc(sizeof(TCandidato));
    return novo;
}

void TCandidato_setInscricao(TCandidato* self, char* inscricao){
    strcpy(self->inscricao, inscricao);
}

void TCandidato_setNome(TCandidato* self, char* nome){
    strcpy(self->nome, nome);
}
void TCandidato_setCurso(TCandidato* self, char* curso){
    strcpy(self->curso, curso);
}
void TCandidato_setScore(TCandidato* self, char* score){
    strcpy(self->score, score);
}

char* TCandidato_toString(TCandidato* self) {
    char* string = malloc(sizeof(char)*256);
    
    string[0] = '\0';
    
    strcat(string, self->inscricao);
    strcat(string, "|");
    strcat(string, self->nome);
    strcat(string, "|");
    strcat(string, self->curso);
    strcat(string, "|");
    strcat(string, self->score);
    strcat(string, "|");
    
    return string;
}
