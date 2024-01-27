/*
	Autore: MAKAOUI YOUNESS
	Copyright:
	Data: xx
	Versione: 1.2 Beta
	Classe: 3E
	Luogo: xx
	Novità versione:
		- 1.1:
			-ottimizzazione
        - 1.2:
            -aggiunta libreria grafica Raylib
            Ancora in revisione
	Descrizione:
			-il programma
*/

#include "struct.h"
#include "campo_1.0.c"
#include "salvattaggi_1.0.c"

// partite giocate
int score = 0;


// genera il campo
void campoDiGioco(tab **pointHead, int s ){

	int i, j, g;
	
	tab *pointTemp = NULL;
	
    printf("\nGenerazione del campo...");
    
    for( g = 0; g < s; g++ ){// genera nv campi richiesti
    	
    	pointTemp = (tab*) malloc(sizeof(tab)); // Allocazione di un nuovo nodo per pointTemp
    	
    	disegnaCampo(pointTemp->campo );
		
		// array che contiene le navi
		oggetto item[14];

		char indice = 48;// indice univoco per ogni nave, parte da 0 = 48 in ASCII

        // genero una matrice per gli indici
		for ( i = 0; i < r; i++ ){
			for ( j = 0; j < c; j++ ){

                pointTemp->cont[i][j] = pointTemp->campo[i][j];
			}
		}
	
	    printf("\nCreo le navi...");

        // numero di navi
        int nv = 0;

        // array contenenti le celle vuote
        const int arr[10] = { 3,5,7,9,11,13,15,17,19,21 };

	    // crea le navi nel campo
	    while( nv < 13 ){
		    
		    item[nv].dim = ( rand() % 4 ) + 1; // dimensione da 1 a 4
		    item[nv].verso = rand() % 2; // verso 1 o 0
		    
			// coordinate da 0 a 9
	    	// coordinate di una nave
	    	item[nv].x = arr[ rand() % 10 ]; // assegno x
	    	item[nv].y = arr[ rand() % 10 ]; // assegno y

		    int x = item[nv].x;
		    int y = item[nv].y;

            // verifica che ci sia spazio per la nave
            int v = 0;

		    // verifico che le celle siano vuote
		    for ( j = 0; j < item[nv].dim; j++ ){

                if ( item[nv].verso == 1 ) {

                    if (pointTemp->campo[x][y] == ' ' && item[nv].dim + x < c ){

                        x += 2;
                        v++;

                    }

                } else if (pointTemp->campo[x][y] == ' ' && item[nv].dim + y < r ){

                    y += 2;
                    v++;
                }
		    }

		    // controllo che lo spazio sia sufficiente per la nave
	        if ( v == item[nv].dim ){
	            
	        	x = item[nv].x;
	        	y = item[nv].y;
	        	
	        	if ( item[nv].verso == 1 ){// stampo le navi verticalmente
		        	
		        	if ( item[nv].dim == 4 ){

                        pointTemp->campo[x][y] = 194;
                        pointTemp->cont[x][y] = indice;
		        		x += 2;
                        pointTemp->campo[x][y] = '|';
                        pointTemp->cont[x][y] = indice;
		        		x += 2;
                        pointTemp->campo[x][y] = '|';
                        pointTemp->cont[x][y] = indice;
		        		x += 2;
                        pointTemp->campo[x][y] = 25;
                        pointTemp->cont[x][y] = indice;
		        		
					} else if ( item[nv].dim == 3 ){

                        pointTemp->campo[x][y] = 194;
                        pointTemp->cont[x][y] = indice;
		        		x += 2;
                        pointTemp->campo[x][y] = '|';
                        pointTemp->cont[x][y] = indice;
		        		x += 2;
                        pointTemp->campo[x][y] = 25;
                        pointTemp->cont[x][y] = indice;
		        		
					} else if ( item[nv].dim == 2 ){

                        pointTemp->campo[x][y] = 194;
                        pointTemp->cont[x][y] = indice;
		        		x += 2;
                        pointTemp->campo[x][y] = 25;
                        pointTemp->cont[x][y] = indice;
		        		
					} else{

                        pointTemp->campo[x][y] = 25;
                        pointTemp->cont[x][y] = indice;
						
					}
					
					indice++;
		        	
		        } else if ( item[nv].verso == 0 ) {// stampo le navi orizzontalmente

                    if (item[nv].dim == 4) {

                        pointTemp->campo[x][y] = 195;
                        pointTemp->cont[x][y] = indice;
                        y += 2;
                        pointTemp->campo[x][y] = 196;
                        pointTemp->cont[x][y] = indice;
                        y += 2;
                        pointTemp->campo[x][y] = 196;
                        pointTemp->cont[x][y] = indice;
                        y += 2;
                        pointTemp->campo[x][y] = 26;
                        pointTemp->cont[x][y] = indice;

                    }
                    if (item[nv].dim == 3) {

                        pointTemp->campo[x][y] = 195;
                        pointTemp->cont[x][y] = indice;
                        y += 2;
                        pointTemp->campo[x][y] = 196;
                        pointTemp->cont[x][y] = indice;
                        y += 2;
                        pointTemp->campo[x][y] = 26;
                        pointTemp->cont[x][y] = indice;

                    }
                    if (item[nv].dim == 2) {

                        pointTemp->campo[x][y] = 195;
                        pointTemp->cont[x][y] = indice;
                        y += 2;
                        pointTemp->campo[x][y] = 26;
                        pointTemp->cont[x][y] = indice;

                    } else {

                        pointTemp->campo[x][y] = 26;
                        pointTemp->cont[x][y] = indice;
                    }

                    indice++;
                }
                nv++;
	        }
		}

        pointTemp->nv = nv;

        pointTemp->pnext = *pointHead;
		
		*pointHead = pointTemp;
	}
    printf("\nGenerazione completata");
}


// elimina le navi indovinate
void affondaNave(tab *pointTemp, int x, int y ){
	
	int i, j;
	
	int len = 0, t = 0;
	
	char s;
	
	if (pointTemp->campo[x][y] == 'X' || pointTemp->campo[x][y] == 'O' ){

		printf("\nHai gia colpito questo punto");
			
	} else if (pointTemp->cont[x][y] >= 48 && pointTemp->cont[x][y] <= 61 ){
		
		// Assegna il carattere 'X' solo dopo la verifica
    	pointTemp->campo[x][y] = 'X';
		
		s = pointTemp->cont[x][y];
		
		for( i = 3; i < r; i++ ){
			for( j = 3; j < c; j++ ){
						
				if(pointTemp->cont[i][j] == s ){
					
					len++;
					
					if(pointTemp->campo[i][j] == 'X' ){
						
						t++;
					}
					
				}
			}
		}
		
		if ( len == t ){
			
			pointTemp->nv--;
		}
	}
}


// genera coordinate leggendo l'input del giocatore
void giocatore(tab **pointHead , char xx, int y ){
	
	tab *pointTemp = (*pointHead);

    pointTemp = pointTemp->pnext;
	
	int x = 3, i;
    
    xx = tolower(xx);
	
	int diff =  xx - 97;
	for( i = 0; i < diff; i++ ){// aumenta il valore di x a seconda del valore di xx
		
		x+=2;
	}
	
	// parametrizzo y in intero
	int n = 0;

	if ( y > 0 && y < 11 ){

		n = ( y + y ) + 1;
		
	} else {

		printf("\nCoordinate non valide");
	}
	
	if( n != 0 ){
		
		y = n;
		
		if (pointTemp->cont[x][y] != ' ' ){
		
			affondaNave(pointTemp, x, y );
			
		} else {

            pointTemp->campo[x][y] = 'O';
		}
			
	} else {
		
		printf("\ninserisci coordinate sensate se vuoi vincere >:(");
	}
}


// genera numeri casuali per le coordinate cpu
void computer( tab **pointHead ){
	
	tab *pointTemp = (*pointHead);

    int x, y;
	
	const int xx[10] = { 3,5,7,9,11,13,15,17,19,21 };
	const int yy[10] = { 3,5,7,9,11,13,15,17,19,21 };

    do{

        x = xx[ rand() % 10 ];
        y = yy[ rand() % 10 ];

    }while(pointTemp->campo[x][y] == 'X' || pointTemp->campo[x][y] == 'O' );

	
	if (pointTemp->campo[x][y] != ' ' ){
		
		affondaNave(pointTemp, x, y );
		
	} else {

        pointTemp->campo[x][y] = 'O';
	}
}


void stampa( tab *pointHead ){

    int i, j;

    tab *pointTemp = pointHead;

    // stampo il campo del giocatore
    printf("\n\n\t\t\t\t\tIl tuo Campo:\t\t\t\t  Campo del computer:");
    for( i = 0; i < r; i++ ){

        printf("\t\t\t\t");

        // Stampare il campo del giocatore
        for( j = 0; j < c; j++ ){

            printf(/*ANSI_COLOR_RED*/"%c"/*ANSI_COLOR_RESET*/, pointTemp->campo[i][j]);
        }

        // Separatore tra i due campi
        printf("\t\t\t\t");

        // Stampare il campo del computer in una seconda matrice
        pointTemp = pointTemp->pnext;

        for( j = 0; j < c; j++ ){

            if(pointTemp->cont[i][j] >= 48 && pointTemp->cont[i][j] <= 62 && pointTemp->cont[i][j] != pointTemp->campo[i][j] && pointTemp->campo[i][j] != 'X' ){

                //pointTemp->campo[i][j] = ' ';
                printf(" ");
            } else {

                printf(/*ANSI_COLOR_RED*/"%c"/*ANSI_COLOR_RESET*/, pointTemp->campo[i][j]);
            }

        }

        printf("\n");
        pointTemp = pointHead;
    }
    pointTemp = pointHead;
}


// inizializza il gioco
int gioco( tab *pontHead ){
	
	campoDiGioco(&pontHead, 2 );

	tab *pointTemp = pontHead;
    
    printf("\nGioca!! ");
    
    int fine = 0;
	
	do{ // loop game

        stampa(pontHead );
		// prendo le coordinate
		printf("\n\t\t\t\t\tHai %d navi rimaste", pointTemp->nv);
        pointTemp = pointTemp->pnext;
		printf("\n\t\t\t\t\tIl computer ha %d navi rimaste", pointTemp->nv);
		
		int y = 0;
		char xx;
		
		printf("\n\t\t\t\t\t Inserisci Le coordinate es.[A9]: ");
		printf("\n\t\t\t\t\t -> ");
    	scanf(" %c",&xx);
    	scanf("%d",&y);

    	if( xx < 65 || xx > 122 ){
    		
    		printf("\nInserisci delle coordinate sensate");
		} else {
			
			giocatore(&pontHead, xx, y );// richiamo funzione giocatore
			
			computer( &pontHead ); // richiamo funzione cpu
		}

        pointTemp = pontHead;
    	
    	pointTemp = pointTemp->pnext;
    	
    	if (pointTemp->nv == 0 ){ // controllo chi ha vinto la partita
    		
    		printf("\nIl computer ha vinto addio NOOB");
    		
    		fine = 1;
    		
    		score++;
		
		} else if (pointTemp->nv == 0 ){
			
			printf("\nhai vinto addio");
			
			fine = 1;
			
			score++;
		}
	}while( !fine );

	
	printf("ADDIO PAZZOIDE");
	
	_sleep(1000);
	
	system("CLS");
	
	return 0;
}


// menu del gioco
void menu(){
	
	// memorizza la scelta dell'utente
	int s;
	
	/*
    questo pezzo di codice fara pare della futura implementazione del multiplayer
    int n;

	printf("\nQuanti giocatori siete? ");
    printf("\n-> ");
    scanf("%d",&n);
    */
    
    tab *pointHead = NULL;
    
    do {
    	
    	printf("\nCiao, Benvenuto a battaglia navale!!\n");
		printf("\n1 - Gioca!!");
		if ( score != 0 ){ printf("\n2 - Score "); }
		printf("\n3 - Lascia un feedback");
	    printf("\n4 - Riavvio");
		printf("\n5 - esci");
		printf("\n-> ");
		scanf("%d",&s);
		
		switch (s){
			
			case 1:{
				
		        gioco(pointHead );
		        		        
		        break;
		    }
			case 2:{
				
				if ( score == 0 ){
					
					printf("\n( Non disponibile )\n"); 
				
				} else {
					
					//stampa( pTab );
				}
				
		        break;
		    }
		    case 3:{
				
		        
		        break;
		    }
			case 4:{
				
		        printf("\nRiavvio effettuato");
		        break;
		    }
		    case 5:{
				
		        printf("\nArrivederci");
		        break;
		    }
			default:{
				
				printf("\nERRORE Commando non riconosciuto");
				break;
			}
		}
		
	}while ( s != 5 );
}


// funzione principale
int main(){

	printf("\nCaricamento...");

	srand(time(NULL));

	menu();

	return 0;
}