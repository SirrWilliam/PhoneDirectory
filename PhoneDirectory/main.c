#include <stdio.h>
#include <conio.h>
#include "Person.h"

#define MaxPerson 32

#define foreach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)

#define clrscr() printf("\033[H\033[J");



struct person *personArray[MaxPerson];

int getPersonArrayCount()
{
    int personArrayCount = 0;
    struct person** pp;
    foreach(pp, personArray) {
        if (*pp != NULL) {
            personArrayCount++;
        }
    }
    return personArrayCount;
}

void addPersonToArray(struct person* new_person)
{
    if (getPersonArrayCount() < MaxPerson) {
        personArray[getPersonArrayCount()] = new_person;
    }
    else {
        printf("Array is full.\n");
    }
}

void removePersonFromArray(int index)
{
    freePerson(personArray[index]);
    personArray[index] = NULL;
    reorderPersonArray();
}

void reorderPersonArray()
{
    int writeIndex = 0;

    for (int readIndex = 0; readIndex < MaxPerson; readIndex++)
    {
        if (personArray[readIndex] != NULL)
        {
            personArray[writeIndex] = personArray[readIndex];

            if (writeIndex != readIndex)
                personArray[readIndex] = NULL;

            writeIndex++;
        }
    }
}

void getListPerson()
{
    printf("+=================+============================+========[%d/%d]==+\n", getPersonArrayCount(), (sizeof(personArray) / sizeof * (personArray)));
    printf("|      Name       |           Surname          |      Number     |\n");
    printf("+=================+============================+=================+\n");
   // printf("[======= Kisi Listesi ==[%d/%d]==]", getListPersonCount(), (sizeof(personArray) / sizeof * (personArray)));
    struct person** pp;
    int counter = 0;
    foreach(pp, personArray) {
        if (*pp != NULL) {
            printf("| %2d %11s  | %-25.25s  | %-*.*s  |\n", counter,(*pp)->name, (*pp)->surname, 14, 14, (*pp)->phoneNumber);
           // printf("\n%s %s %s", (*pp)->name, (*pp)->surname,(*pp)->phoneNumber);
        }
        counter++;

    }
    printf("+=================+============================+=================+\n");
   // printf("\n[================================]");
}

void fillPersonArray() {
    personArray[0] = createPerson("Brecken", "Estes", "555555555555");
    personArray[1] = createPerson("Marianna", "Schneider", "555555555555");
    personArray[2] = createPerson("Clarissa", "Kelley", "555555555555");
    personArray[3] = createPerson("Journi", "Bowman", "555555555555");
    personArray[4] = createPerson("Angelina", "Yates", "555555555555");
    personArray[5] = createPerson("Hunter", "Corona", "555555555555");
    personArray[6] = createPerson("Charleigh", "Cuevas", "555555555555");
    personArray[7] = createPerson("Amir", "Griffin", "555555555555");
    personArray[8] = createPerson("Emirhan", "Taç", "555555555555");
    personArray[9] = createPerson("Larry", "Mathis", "555555555555");
    personArray[10] = createPerson("Gage", "Thomas", "555555555555");
    personArray[11] = createPerson("Landry", "McConnell", "555555555555");
    personArray[12] = createPerson("Coen", "Barron", "555555555555");
}

int main()
{
    fillPersonArray();

    int index = -1;
    while (1)
    {
        printf("\nTelefon Rehber\n 1.Listele\n 2.Yeni Kisi Ekle\n 3.Kisi Sil\n");
        printf("> ");
        scanf_s("%d", &index, 1);

        switch (index)
        {
        case 1:
            clrscr();
            getListPerson(personArray);
            break;
        case 2:
            clrscr();

            char _name[64];
            char _surname[64];
            char _phoneNumber[64];

            printf("Yeni Kisi Ekle\n");
            printf("Ad >");
            scanf_s("%s", &_name,64);
            printf("\nSoyad >");
            scanf_s("%s", &_surname, 64);
            printf("\nNumara >");
            scanf_s("%s", &_phoneNumber, 64);
            addPersonToArray(createPerson(_name, _surname, _phoneNumber));
            break;
        case 3:
            clrscr();

            int delIndex = -1;

            printf("Kisi Sil [-2 CANCEL]\n");
            printf("Siralama >");
            scanf_s("%d", &delIndex, 1);

            if (delIndex = -2)
            {
                clrscr();
                break;
            }
            removePersonFromArray(delIndex);
            break;
        default:
            index = -1;
            break;
        }
    }
    return 0;
}