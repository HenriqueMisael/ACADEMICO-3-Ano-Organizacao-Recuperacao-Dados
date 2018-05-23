#include "TCandidato.h"
#include "TScan.h"
#include "TFile.h"

void escreveCandidato(TCandidato* c) {
    printf("%s\n", TCandidato_toString(c));
}

void leCandidato(TCandidato* c) {
    TCandidato_setInscricao(c, TScan_get("Inscricao: ", TAMANHO_CAMPO_INSCRICAO));
    TCandidato_setNome(c, TScan_get("Nome: ", TAMANHO_CAMPO_NOME));
    TCandidato_setCurso(c, TScan_get("Curso: ", TAMANHO_CAMPO_CURSO));
    TCandidato_setScore(c, TScan_get("Score: ", TAMANHO_CAMPO_SCORE));
}

void readField(char* field, int fieldSize, FILE *input){
    char c;
    int i;

    for(i = 0; i < fieldSize; i++){
        c = fgetc(input);
        if(c == '|'){
            field[i] = '\0';
            break;
        }
        field[i] = c;
    }
}

void importacao() {
    FILE* file = fopen("dados-inline.txt", "r");
    TCandidato* c = TCandidato_novo();
    
    while(!feof(file)) {
        readField(c->inscricao, TAMANHO_CAMPO_INSCRICAO,file);
        readField(c->nome, TAMANHO_CAMPO_NOME,file);
        readField(c->curso, TAMANHO_CAMPO_CURSO,file);
        readField(c->score, TAMANHO_CAMPO_SCORE,file);
        
        if(feof(file))
            break;
        TFile_append(c);
    }
    
    fclose(file);
}

void insercao() {
    TCandidato* c = TCandidato_novo();
    
    leCandidato(c);
    printf("Inserir candidato: \n");
    escreveCandidato(c);
    
    if(strcmp(TScan_get("[ /N]", 2), "N")) {
        TFile_append(c);
    }
}

int menu() {
    printf(" 1 - Importar dados\n");
    printf(" 2 - Inserir candidato\n");
    printf(" 3 - Remover candidato\n");
    printf(" 4 - Renovar arquivo\n");
    
    return TScan_getLong("> ");
}

int main(int argc, char *argv[]) {
	
	int opcao;
	
	TFile_verify();
	
	do{
	    opcao = menu();
    	switch(opcao){
    	    case 1: importacao(); break;
    	    case 2: insercao(); break;
    	    case 3: TFile_remove(TScan_get("Inscricao a remover: ", TAMANHO_CAMPO_INSCRICAO)); break;
    	    case 4: TFile_createNewFile(); break;
    	    default: if(opcao) printf("\n Opcao nao prevista.");
        }
    } while(opcao);
    
    return 0;
}
