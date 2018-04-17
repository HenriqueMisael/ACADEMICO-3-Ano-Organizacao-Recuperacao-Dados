#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "person.c"
#include "indicatedFile.c"

int quitEditing(TPerson* person){
    return person->lastName[0] == 27;
}

void cleanString(char* string, int maxSize){
	int i;

	for(i = 0; i < maxSize; i++)
		if(string[i] == 10 || string[i] == 13){
			string[i++] = 0;
            break;
        }
}

char* askEntry(char* text, int entrySize){
	char* entry = malloc(sizeof(char)*entrySize);

	printf("\n %s: ", text);
	fgets(entry, entrySize+1, stdin);

	cleanString(entry,entrySize+1);

	return entry;
}

FILE* openFile(char* mode){

    char* fileName = "teste.txt";
	FILE* file = fopen(fileName, mode);

	if(!file)
		printf("Arquivo %s nao pode ser aberto.", fileName);

	return file;
}

void askPersonData(TPerson* person){
    strcpy(person->lastName , askEntry("Digite o ultimo nome"  , PERSON_SIZE_LASTNAME));
	strcpy(person->firstName, askEntry("Digite o primeiro nome", PERSON_SIZE_FIRSTNAME));
	strcpy(person->address  , askEntry("Digite o enderecoo"	   , PERSON_SIZE_ADDRESS));
	strcpy(person->city		, askEntry("Digite a cidade"	   , PERSON_SIZE_CITY));
	strcpy(person->state	, askEntry("Digite o estado"	   , PERSON_SIZE_STATE));
	strcpy(person->zipCode	, askEntry("Digite o CEP"		   , PERSON_SIZE_ZIPCODE));
    // strcpy(person->lastName , "Machado");
    // strcpy(person->firstName, "Henrique Misael");
    // strcpy(person->address  , "Av Joao Paulino Vieira Filho");
    // strcpy(person->city		, "Maringa");
    // strcpy(person->state	, "PR\0");
    // strcpy(person->zipCode	, "87020015");
}

void personRegistry(){
    TPerson* person = TPerson_New();
	FILE* output = openFile("a");

	if(output){
		askPersonData(person);
		writePersonData(output, person);
		fclose(output);
	}
}

void showPersonData(TPerson* person){
    printf("Nome: %s %s\n", person->firstName, person->lastName);
}

void listPeople(){
    TPerson* person = TPerson_New();
	FILE* input = openFile("r");

	if(input){
        while(1){
            if(!readPersonData(input, person))
                break;
            showPersonData(person);
        }
	}
}

int menuPrincipal(){

    char opcao[1];
    int opcaoSelecionada;

    printf(" Cadastro de pessoas\n");
    printf(" 1-Cadastrar pessoa\n");
    printf(" 2-Mostrar pessoas\n");
    printf(" 0-Finalizar programa\n");

    strcpy(opcao, askEntry("Escolha a opcao", 1));
    opcaoSelecionada = opcao[0] - '0';
    getchar();

    switch(opcaoSelecionada){
        case 1: personRegistry();break;
        case 2: listPeople();break;
    }

    return opcaoSelecionada;
}

int main(){

    while(menuPrincipal())

    return 0;
}
