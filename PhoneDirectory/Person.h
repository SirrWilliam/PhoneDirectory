#pragma once
#ifndef PERSON_H
#define PERSON_H

struct person {
    char *name;
    char *surname;
    char phoneNumber[13];
};

struct person *createPerson(char *name, char *surname, char *phoneNumber);

void freePerson(struct person* p);

#endif /* PERSON_H */