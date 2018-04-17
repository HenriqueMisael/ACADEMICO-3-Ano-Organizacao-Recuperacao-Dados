#include <stdio.h>
#include <malloc.h>
#include "person.h"

TPerson* TPerson_New(){
    return (TPerson*)malloc(sizeof(TPerson));
}
