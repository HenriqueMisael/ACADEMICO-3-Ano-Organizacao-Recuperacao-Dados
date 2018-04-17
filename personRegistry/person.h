#include <stdio.h>

#define PERSON_SIZE_LASTNAME  25
#define PERSON_SIZE_FIRSTNAME 25
#define PERSON_SIZE_ADDRESS   50
#define PERSON_SIZE_CITY      30
#define PERSON_SIZE_STATE     2
#define PERSON_SIZE_ZIPCODE   8

typedef struct {
    char firstName[PERSON_SIZE_LASTNAME];
    char lastName[PERSON_SIZE_FIRSTNAME];
    char address[PERSON_SIZE_ADDRESS];
    char city[PERSON_SIZE_CITY];
    char state[PERSON_SIZE_STATE];
    char zipCode[PERSON_SIZE_ZIPCODE];
} TPerson;
