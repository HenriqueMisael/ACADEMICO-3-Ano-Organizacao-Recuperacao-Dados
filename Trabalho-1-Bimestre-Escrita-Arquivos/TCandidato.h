#include <stdio.h>
#include <malloc.h>
#include <strings.h>

#ifndef TCANDIDATO_H
    #define TCANDIDATO_H
    #define TAMANHO_CAMPO_INSCRICAO  10
    #define TAMANHO_CAMPO_NOME       40
    #define TAMANHO_CAMPO_CURSO      40
    #define TAMANHO_CAMPO_SCORE      10
    
    typedef struct {
        char inscricao[TAMANHO_CAMPO_INSCRICAO];
        char nome[TAMANHO_CAMPO_NOME];
        char curso[TAMANHO_CAMPO_CURSO];
        char score[TAMANHO_CAMPO_SCORE];
    } TCandidato;
    
    TCandidato* TCandidato_novo();
    void TCandidato_setInscricao(TCandidato* self, char* inscricao);
    void TCandidato_setNome(TCandidato* self, char* nome);
    void TCandidato_setCurso(TCandidato* self, char* curso);
    void TCandidato_setScore(TCandidato* self, char* score);
    char* TCandidato_toString(TCandidato* self);
#endif
