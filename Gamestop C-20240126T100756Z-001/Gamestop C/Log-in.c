/*
	Nome: Login in c
	Copyright: xx
	Autore: Youness Makaoui
	Luogo: xx
	Versione: xx
	Componenti: xx
	Data: xx
	Descrizione: xx
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct user{
	
	char name[20];
	char email[20];
	char password[20];
	int age;
    struct user* next;

}User;

typedef struct{
    User* user;

}dataBase;

int hash( char index ){

    int n = index - 'a';
    return n;
}

int checkIn( char* name, char* lastName, dataBase array[] ){

	int n = hash( name[0] );

    strcpy( array[n].user->name, name );
    strcpy( array[n].user->email, lastName );

    return n;
}

int LoginMain(){

    dataBase array[26];
	char name[20] = {""}, lastName[20] = {""}, verify;

    for( int i = 0; i < 26; i++ ){
        array[i].user = (User*) malloc(sizeof(User*));
        array[i].user->next = NULL;
    }
	
	do{
		
		printf("\nInserisci Nome e cognome:\n-> ");
		scanf("%19s %19s",name ,lastName);
		fflush(stdin);
		
		printf("\nCredenziali corrette?: y/n\n->");
		scanf(" %c",&verify);
		fflush(stdin);
		
	}while( verify != 'y' );

    int outcome;

    if( ( name[0] < 'a' || name[0] > 'z' ) || ( lastName[0] < 'a' || lastName[0] > 'z' ) ){

        printf("\nLe credenziali devono iniziare SOLO con caratteri alfabetici");

    } else {

        outcome = checkIn( name, lastName, array );
        printf("\nUtente trovato %d - %s", outcome, array[outcome].user->name);
    }

    for ( int i = 0; i < 26; ++i ){
        free(array[i].user);
    }
	exit (0);
}