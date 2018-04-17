#include <stdio.h>

void writeField(char* field, FILE *output){
    fputs(field, output);
    fputs("|", output);
}

void writePersonData(FILE* output, TPerson* person){
	writeField(person->lastName , output);
	writeField(person->firstName, output);
	writeField(person->address  , output);
	writeField(person->city     , output);
	writeField(person->state    , output);
	writeField(person->zipCode  , output);

	fputs("\n", output);
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

void goNextLine(FILE *file){
    char c;

    do{
        c = fgetc(file);
    }while(c != '\n');
}

int readPersonData(FILE* input, TPerson* person){
    if(fgetc(input) == EOF)
        return 0

    fseek(input, -1, SEEK_CUR);

    readField(person->lastName , PERSON_SIZE_LASTNAME , input);
	readField(person->firstName, PERSON_SIZE_FIRSTNAME, input);
	readField(person->address  , PERSON_SIZE_ADDRESS  , input);
	readField(person->city     , PERSON_SIZE_CITY     , input);
	readField(person->state    , PERSON_SIZE_STATE    , input);
	readField(person->zipCode  , PERSON_SIZE_ZIPCODE  , input);
    goNextLine(input);
}
