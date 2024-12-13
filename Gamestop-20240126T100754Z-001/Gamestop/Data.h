#ifndef LAVORI_C_DATA_H
#define LAVORI_C_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define r 100
#define d 1000

typedef struct user{

    char name[r];
    char surname[r];
    char email[r];
    char password[r];
    char address[r];
    int age;
    struct user *previous;
    struct user *next;

}User;

#endif //LAVORI_C_DATA_H
