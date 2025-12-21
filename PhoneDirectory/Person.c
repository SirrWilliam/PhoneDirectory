#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Person.h"

struct person *createPerson(char *name, char *surname, char *phoneNumber) {
    if (name == NULL || surname == NULL || phoneNumber == NULL) {
        printf("ERROR");
        return NULL;
    }
    struct person *p = malloc(sizeof(*p));
    if (p == NULL) {
        printf("ERROR");
        return NULL;
    }

    size_t nameLen = strlen(name) + 1;
    size_t surnameLen = strlen(surname) + 1;
    size_t phoneNumberLen = sizeof((*p).phoneNumber);

    size_t _phoneNumberLen = strlen(phoneNumber) + 1;

    p->name = malloc(nameLen);
    p->surname = malloc(surnameLen);
    //phoneNumber is already allocated.

    if (_phoneNumberLen > phoneNumberLen) {
        printf("Phone number is too long.");
        freePerson(p);
        return NULL;
    }

    strcpy_s((*p).phoneNumber, phoneNumberLen, phoneNumber);
    strcpy_s((*p).name, nameLen, name);
    strcpy_s((*p).surname, surnameLen, surname);

    return p;
};

void freePerson(struct person* p) {
    if (p == NULL) return;
    free((*p).name);
    free((*p).surname);
    //free(p->phoneNumber);
    free(p);
}