/*
	Nome: Somma due numeri
	Copyright: xx
    Numero: 2
    Source: LeetCode
	Autore: Makaoui Youness
	Luogo: 3G
	Versione: 1
	Data: 29/05/2024
	Descrizione:
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Number{

    int n;
    struct Number *next;

}Num;

int numero( Num *head ){

    int size = (int) rand()% 15;
    head = (Num*) malloc(sizeof(Num));
    Num *temp = (Num*) malloc(sizeof(Num));

    if ( head == NULL || temp == NULL )
        return 0;

    int i;
    head->n = rand() % 10;
    head->next = temp;
    for (i = 0; i < size; ++i) {
        temp->n = rand() % 10;
        temp->next = (Num*) malloc(sizeof(Num));
        temp = temp->next;
        temp->next = NULL;
    }

    free(temp);
    return 1;
}

int main() {

    srand(time(NULL));

    Num *num1;
    Num *num2;

    if ( numero(num1) == 0 || numero(num2) == 0 ) {
        printf("\nOut of Memory");
        return 5;
    }

    Num *temp = num1;
    while ( temp->next != NULL ){
        printf("\n%d",temp->n);
        temp = temp->next;
    }

    free(temp);
    free(num1);
    free(num2);
}