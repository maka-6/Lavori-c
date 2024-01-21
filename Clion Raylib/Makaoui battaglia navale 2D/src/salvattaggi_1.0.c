/*
	Nome: Salvataggio su file
	Versione: 1.0
	Data: 21/01/2024
*/

#include "struct.h"

// salva i punteggi delle partite
int saveOnFile( tab *ptesta ){

    FILE *pfile = fopen( "score.txt","w+" );

    int i = 0;

    char str[r];

    int num = 0;

    if( pfile != NULL ){// controllo che il file esista


        tab *ptemp = ptesta;
        tab *ptemp2 = ptemp->pnext;

        part *pTesta = NULL;
        part *pTemp = NULL;

        printf("\nInserisci il tuo nome campione\n-> ");
        gets(str);
        fflush(stdin);

        while( i != 1 ){

            pTemp = ( part* ) malloc(sizeof( part ) ); // Allocazione di un nuovo nodo

            strcpy( pTemp->vincitore, str );

            pTemp->nvC = ptemp2->nv; // assegno il numero di navi
            pTemp->nvG = ptemp->nv; // assegno il numero di navi

            fprintf( pfile, "\nVincitore: %s", pTemp->vincitore );
            fprintf( pfile, "\nNavi rimaste al computer: %d", pTemp->nvC );
            fprintf( pfile, "\nNavi rimaste a %s: %d", str,pTemp->nvG );

            pTemp->pnext = pTesta;

            pTesta = pTemp;

            i++;
        }

        fclose (pfile);

        num = 1;

    }

    free(ptesta);

    return num;
}
