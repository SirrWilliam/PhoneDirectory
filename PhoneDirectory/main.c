#include <stdio.h>
#include <conio.h>
#include "Person.h"
#include "Macro.h"
#include <Windows.h>
#include "appState.h"

#define MaxPerson 32
#define Delay 250

struct person *personArray[MaxPerson];

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

void getListPerson()
{

    printf(" +=======+=================+============================+========[%d/%d]==+\n", getPersonArrayCount(), (sizeof(personArray) / sizeof * (personArray)));
    printf(" | Index |      Name       |           Surname          |      Number     |\n");
    printf(" +=======+=================+============================+=================+\n");
   // printf("[======= Kisi Listesi ==[%d/%d]==]", getListPersonCount(), (sizeof(personArray) / sizeof * (personArray)));
    struct person** pp;
    int counter = 0;
    foreach(pp, personArray) {
        if (*pp != NULL) {
            printf(" |  %2d   | %-11s     | %-25.25s  | %-*.*s  |\n", counter,(*pp)->name, (*pp)->surname, 14, 14, (*pp)->phoneNumber);
           // printf("\n%s %s %s", (*pp)->name, (*pp)->surname,(*pp)->phoneNumber);
        }
        counter++;
    }
    printf(" +=======+=================+============================+=================+\n");
   // printf("\n[================================]");
}

void setWindow()
{
    SetConsoleTitleA("Phone Directory");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND hwnd = GetConsoleWindow();

    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~WS_SIZEBOX & ~WS_MAXIMIZEBOX;
    SetWindowLong(hwnd, GWL_STYLE, style);

    HMENU menu = GetSystemMenu(hwnd, FALSE);
    DeleteMenu(menu, SC_SIZE, MF_BYCOMMAND);
    DeleteMenu(menu, SC_MAXIMIZE, MF_BYCOMMAND);
    DrawMenuBar(hwnd);

    SHORT cols = 75, rows = 30;
    SMALL_RECT win = { 0, 0, cols - 1, rows - 1 };
    COORD buf = { cols, rows };

    SetConsoleWindowInfo(hOut, TRUE, &win);
    SetConsoleScreenBufferSize(hOut, buf);
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
    personArray[8] = createPerson("Sir", "William", "555555555555");
    personArray[9] = createPerson("Larry", "Mathis", "555555555555");
    personArray[10] = createPerson("Gage", "Thomas", "555555555555");
    personArray[11] = createPerson("Landry", "McConnell", "555555555555");
    personArray[12] = createPerson("Coen", "Barron", "555555555555");
}

void printTitle()
{
    printf("                           PHONE DIRECTORY v0.5                            \n");
    printf("           (C) NOCOPYRIGHT 2025 EMIRHAN TAC, PIRI REIS UNIVERSITY          \n\n\n");
}

int isNumber(char* stringArray)
{

    //go through each character
    //location in the array until
    //we reach the null character (end of input)
    for (int i = 0; stringArray[i] != '\000'; i++)
    {
        if (isdigit(stringArray[i]) == 0)//if the current character is not a digit....
            return 0; //return false and end function here

    }

    return 1;//return true since the entire array contained numeric characters
}

int readInt(const char* prefix, int *outInt)
{
    char buffer[64];

    while (1) {
        printf("%s < ", prefix);

        if (!fgets(buffer, sizeof buffer, stdin)) {
            puts("INPUT ERROR OR EOF");
            return 0; // fail
        }

        size_t len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            --len;
        }

        if (len == 0) {
            puts("EMPTY INPUT!");
            continue;
        }

        if (!isNumber(buffer)) {
            puts("NUMBER ONLY!");
            continue;
        }

        *outInt = atoi(buffer);

        return 1;
    }
}

int readString(const char* prefix, char* outStr, size_t outSize)
{
    char buffer[64];

    while (1) {
        printf("%s < ", prefix);

        if (!fgets(buffer, sizeof buffer, stdin)) {
            puts("INPUT ERROR OR EOF");
            return 0; // fail
        }

        size_t len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            --len;
        }

        if (len == 0) {
            puts("EMPTY INPUT!");
            continue;
        }

        if (len >= outSize) {
            puts("INPUT TOO LONG!");
            continue;
        }


        if (strcpy_s(outStr, outSize, buffer) != 0) {
            puts("COPY ERROR");
            return 0;
        }

        return 1; 
    }
}


int main()
{
    setWindow();
    fillPersonArray();

    AppState state = STATE_WAIT_START;
    int key;

    while (1)
    {
        switch (state)
        {
            case STATE_WAIT_START:
                clrscr();
                printTitle();
                printf("                         PRESS ANY KEY TO CONTINUE                         \n");
                _getch();
                state = STATE_MAIN_MENU;
                break;
            case STATE_MAIN_MENU:
                clrscr();
                printTitle();
                printf("SAVED PERSON COUNT: %d\n", getPersonArrayCount());
                printf("\n\n L-LIST PERSON   | N-ADD NEW PERSON | D-DELETE PERSON \n U-UPDATE PERSON | ESC-EXIT\n");

                key = _getch();
                switch (key)
                {
                case 'l':
                case 'L':
                    Sleep(Delay);
                    state = STATE_LIST;
                    break;

                case 'n':
                case 'N':
                    Sleep(Delay);
                    state = STATE_ADD;
                    break;

                case 'd':
                case 'D':
                    Sleep(Delay);
                    state = STATE_DELETE;
                    break;
                case 27:
                    Sleep(Delay);
                    clrscr();
                    exit(EXIT_SUCCESS);
                    break;
                }
                break;
            case STATE_LIST:
                clrscr();
                printTitle();
                getListPerson(personArray);
                printf("\nB-BACK\n");

                key = _getch();
                if (key == 'b' || key == 'B')
                {
                    Sleep(Delay);
                    state = STATE_MAIN_MENU;
                }
                break;
            case STATE_ADD:
                clrscr();
                printTitle();

                char _name[64];
                char _surname[64];
                char _phoneNumber[64];

                printf("ADD NEW PERSON\n");             
                readString("NAME", _name, sizeof _name);
                readString("SURNAME", _surname, sizeof _surname);
                readString("NUMBER", _phoneNumber, sizeof _phoneNumber);
                addPersonToArray(createPerson(_name, _surname, _phoneNumber));
                Sleep(Delay);
                state = STATE_MAIN_MENU;
                break;
            case STATE_DELETE:
                printTitle();
                clrscr();

                int delIndex = 0;

                printf("DELETE PERSON [-1 CANCEL]\n");
                readInt("INDEX", &delIndex);


                if (delIndex == -1)
                {
                    clrscr();
                    Sleep(1000);
                    state = STATE_MAIN_MENU;
                }
                removePersonFromArray(delIndex);
                Sleep(Delay);
                state = STATE_MAIN_MENU;
                break;
        }
      
    }
 
   
   
      /*  switch (index)
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
            scanf_s("%s", &_name, 64);
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
        }*/
    return 0;
}
