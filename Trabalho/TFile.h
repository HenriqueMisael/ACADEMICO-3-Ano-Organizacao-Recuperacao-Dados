#include "TCandidato.h"

void TFile_createNewFile();
void TFile_verify();
void TFile_append(TCandidato* c);
void TFile_remove(char* inscricao);
FILE* openFileToUse();
void gravaNovoRegistro(char* buffer, short tamanho);
int TFile_seek(int inscricao);
int getInscricaoRegistroAtual();
void TFile_showContent();
void TFile_avancaNoLed();
void TFile_retornaNoLed();
int achaEspacoDisponivel(short tamanho, long* proximoOffsetLed);
void TFile_posicionaInicio();
void TFile_posicionaFim();
void TFile_avancaTamanho();
void TFile_retornaTamanho();
void TFile_avancaMarcadorDelecao();
void TFile_retornaMarcadorDelecao();
