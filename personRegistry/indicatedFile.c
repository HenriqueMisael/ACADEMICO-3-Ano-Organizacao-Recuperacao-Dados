#include <stdio.h>
#include <string.h>

void writeField(char *buffer, char* field){
    strcat(buffer,field);
    strcat(buffer,"|");
}

void writeOnFile(char* writableString, FILE* file){
    int size = strlen(writableString);

    fwrite(&size, sizeof(char), 1, file);
    fputs(writableString, file);
}

void writePersonData(FILE* output, TPerson* person){

    char buffer[256];

    buffer[0] = '\0';

    writeField(buffer, person->lastName );
	writeField(buffer, person->firstName);
	writeField(buffer, person->address  );
	writeField(buffer, person->city     );
	writeField(buffer, person->state    );
	writeField(buffer, person->zipCode  );

    writeOnFile(buffer, output);
}

void goNextLine(FILE *file){
    char c;

    do{
        c = fgetc(file);
    }while(c != '\n');
}

void readPersonStream(char* personStream, int size, FILE* input){
    int i;

    for(i = 0; i < size; i++){
        personStream[i] = fgetc(input);
    }

    personStream[i] = '\0';
}

void getField(char* field, char* buffer){
    if(buffer)
        strcpy(field, buffer);
}

int readPersonData(FILE* input, TPerson* person){

    char* personStream;
    int size;

    size = fgetc(input);

    if(size == EOF)
        return 0;

    personStream = malloc(sizeof(char)*size+1);
    readPersonStream(personStream, size, input);

	getField(person->lastName , strtok(personStream, "|"));
	getField(person->firstName, strtok(NULL, "|"));
	getField(person->address  , strtok(NULL, "|"));
	getField(person->city     , strtok(NULL, "|"));
	getField(person->state    , strtok(NULL, "|"));
	getField(person->zipCode  , strtok(NULL, "|"));

    return 1;
}
