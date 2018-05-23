#include "TCandidato.h"

void TFile_createNewFile();
void TFile_verify();
void TFile_append(TCandidato* c);
void TFile_remove(char* inscricao);
FILE* openFileToUse();
void gravaNovoRegistro(char* buffer, short tamanho);
int TFile_seek(int inscricao);
int getInscricaoRegistroAtual();
