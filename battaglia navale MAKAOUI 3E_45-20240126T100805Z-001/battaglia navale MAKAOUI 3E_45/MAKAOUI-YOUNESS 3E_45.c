/*
	Autore: MAKAOUI YOUNESS
	Copyright: nessuno
	Data: xx
	Versione: 1.0 Beta
	Classe: 3E
	Luogo: xx
	Novita' versione:
		- 1.0:
			Ancora in revisione
	Descrizione:
			-il programma simula battaglia navale contro la cpu
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>


#define r 23 // definisco 23 righe
#define c 23 // definisco 23 colonne
#define DIM 50 // dimensione degli array


// numero di partite giocate
int score = 0;

// struct di una nave
typedef struct{
	
	int dim;// dimensione della nave
	
	// x e y sono le coordinate della nave
	int x;
	int y;
	
	int verso;// indica il verso della nave 0 orizzontale, 1 verticale
	
}oggetto;


// struct di una matrice
typedef struct tab{
	
	char campo[r][c]; // matrice contenente il campo
	
	char cont[r][c]; // matrice contenente gli indici univoci per ogni nave
	
	int nv; // numero di navi rimaste 
	
	struct tab *pnext;
	
}tab;


// struct della stampa nel file
typedef struct part{
	
	char vincitore[r]; // nome del vincitore
	
	int nvG; // numero navi del giocatore rimaste
	
	int nvC; // numero navi della cpu rimaste
	
	struct part *pnext;
	
}part;


// genera il campo
void campoGioco( tab **ptesta, int s ){

	int i, j, g, l;
	
	tab *ptemp = NULL;
	
    printf("\nGenerazione del campo...");
    
    for( g = 0; g < s; g++ ){// genera i campi richiesti
    	
    	ptemp = (tab*) malloc(sizeof(tab)); // Allocazione di un nuovo nodo

		//riempe la matrice di caratteri vuoti
		memset( ptemp->campo, ' ', sizeof(ptemp->campo));
	
	    char lett = 65, num = 49; // variabili che convertono i numeri in caratteri num = numeri e lett = alfabetici
	    
	    // scrivo lettere e numeri
		for ( i = 3; i < c - 1; i+=2 ){
			
			//assegno i numeri alle loro posizioni orizzontalo
			ptemp->campo[1][i] = num;
			num++;
			ptemp->campo[1][21] = 'X';// X sostituisce il 10 essendo una stringa
			
		    //assegno le lettere alle loro posizioni verticali
		    ptemp->campo[i][0] = lett;
		    lett++;
		}
		
		//creo il campo i bordi e le celle del campo 10x10 nella matrice 24x24
		 for ( i = 3; i < r - 1; i+=2 ){
		 	
			ptemp->campo[i][2] = '|';
			ptemp->campo[i+1][2] = 195;
			ptemp->campo[i][22] = '|';
			ptemp->campo[i+1][22] = 180;
			ptemp->campo[2][i] = 196;
			ptemp->campo[2][i+1] = 194;
			ptemp->campo[22][i] = 196;
			ptemp->campo[22][i+1] = 193;
		}
	
		//creo i bordi delle singole celle
		for ( i = 4; i < r - 1; i+=2 ){
			
			for ( j= 3; j < c; j+=2 ){
				
				ptemp->campo[i][j]=196;
			}
			
			for ( j = 4; j < c - 1; j+=2 ){
				
				ptemp->campo[i][j] = 197;
				ptemp->campo[i-1][j] = '|';
				ptemp->campo[21][i] = '|';
			}
		}
		
		//creo gli angoli
		ptemp->campo[2][2] = 218;
		ptemp->campo[22][2] = 192;
		ptemp->campo[22][22] = 217;
		ptemp->campo[2][22] = 191;
	
		// array che contiene le navi
		oggetto item[20]; 
		
		char indice = 48;// indice univoco per ogni nave
	
		// numero di navi
		int nv = 0;

        // copio la matrice campo in quella per gli indici univoci
		for ( i = 0; i < r; i++ ){
			for ( j = 0; j < c; j++ ){
			
				ptemp->cont[i][j] = ptemp->campo[i][j];
			}
		}
	
	    printf("\nCreo le navi...");
	    
	    // crea le navi nel campo
	    for ( i = 0; i < 20; i++ ){
	    	
	    	// verifica che ci sia spazio per la nave
		    int v = 0;
		    
		    item[i].dim = rand() % 4 + 1; // la dimensione va da 1 a 4
		    item[i].verso = rand() % 2; // la dimensione va da 1 a 4

            // array contenenti le celle vuote
		    const int arr[10] = { 3,5,7,9,11,13,15,17,19,21 };
	
			int nx = rand() % 10; // le coordinate vanno da 0 a 9
	    	int ny = rand() % 10; // le coordinate vanno da 0 a 9
	    	
	    	// coordinate di una nave
	    	item[i].x = arr[nx]; // assegno x
	    	item[i].y = arr[ny]; // assegno y

		    int x = item[i].x;
		    int y = item[i].y;
		    
		    // verifico che le celle selezionate non siano gia occupate
		    for ( j = 0; j < item[i].dim; j++ ){
					
                if ( item[i].verso == 1 && ptemp->campo[x][y] == ' ' ){

                    if ( ( item[i].dim + x )<= 23 ){

                        x += 2;
                        v++;
                    }


                } else if ( item[i].verso == 0 && ptemp->campo[x][y] == ' ' ){

                    if ( ( item[i].dim + y )<= 23 ){

                        y += 2;
                        v++;
                    }
                }
		    }
			
		    // controllo che lo spazio sia sufficiente per la nave
	        if ( v == item[i].dim ){
	        	
	            nv++; // incremento il numero di navi
	            	
	        	x = item[i].x;
	        	y = item[i].y;
	        	
	        	if ( item[i].verso == 1 ){// stampo le navi verticalmente
		        	
		        	if ( item[i].dim == 4 ){
		        		
		        		ptemp->campo[x][y] = 194;
		        		ptemp->cont[x][y] = indice;
		        		x += 2;
		        		ptemp->campo[x][y] = '|';
		        		ptemp->cont[x][y] = indice;
		        		x += 2;
		        		ptemp->campo[x][y] = '|';
		        		ptemp->cont[x][y] = indice;
		        		x += 2;
		        		ptemp->campo[x][y] = 25;
		        		ptemp->cont[x][y] = indice;
		        		
					} else if ( item[i].dim == 3 ){
						
						ptemp->campo[x][y] = 194;
						ptemp->cont[x][y] = indice;
		        		x += 2;
		        		ptemp->campo[x][y] = '|';
		        		ptemp->cont[x][y] = indice;
		        		x += 2;
		        		ptemp->campo[x][y] = 25;
		        		ptemp->cont[x][y] = indice;
		        		
					} else if ( item[i].dim == 2 ){
						
						ptemp->campo[x][y] = 194;
						ptemp->cont[x][y] = indice;
		        		x += 2;
		        		ptemp->campo[x][y] = 25;
		        		ptemp->cont[x][y] = indice;
		        		
					} else{
						
						ptemp->campo[x][y] = 25;
						ptemp->cont[x][y] = indice;
						
					}
					
					indice++;
		        	
		        } else if ( item[i].verso == 0 ){// stampo le navi orizzontalmente
		        	
		        	if ( item[i].dim == 4 ){
		        		
		        		ptemp->campo[x][y] = 195;
		        		ptemp->cont[x][y] = indice;
		        		y += 2;
		        		ptemp->campo[x][y] = 196;
		        		ptemp->cont[x][y] = indice;
		        		y += 2;
		        		ptemp->campo[x][y] = 196;
		        		ptemp->cont[x][y] = indice;
		        		y += 2;
		        		ptemp->campo[x][y] = 26;
		        		ptemp->cont[x][y] = indice;
		        		
					} if ( item[i].dim == 3 ){
						
						ptemp->campo[x][y] = 195;
						ptemp->cont[x][y] = indice;
		        		y += 2;
		        		ptemp->campo[x][y] = 196;
		        		ptemp->cont[x][y] = indice;
		        		y += 2;
		        		ptemp->campo[x][y] = 26;
		        		ptemp->cont[x][y] = indice;
		        		
					} if ( item[i].dim == 2 ){
						
						ptemp->campo[x][y] = 195;
						ptemp->cont[x][y] = indice;
		        		y += 2;
		        		ptemp->campo[x][y] = 26;
		        		ptemp->cont[x][y] = indice;
		        		
					} else{
						
						ptemp->campo[x][y] = 26;
						ptemp->cont[x][y] = indice;
					}
					
					indice++;
				}
	        }
	        
	        v = 0;
	        
		}
		
		ptemp->nv = nv;
		
		ptemp->pnext = *ptesta;
			
		*ptesta = ptemp;
	}

    printf("\nGenerazione completata");

}


// parametrizza le coordinate
int parametrizza( int x ){
	
	int n = 0; // il numero parametrizzato che restituisco
	
	switch ( x ){
		
		case 1:{
			
			n = 3;
			break;
		}
		case 2:{
			
			n = 5;
			break;
		}
		case 3:{
			
			n = 7;
			break;
		}
		case 4:{
			
			n = 9;
			break;
		}
		case 5:{
			
			n = 11;
			break;
		}
		case 6:{
			
			n = 13;
			break;
		}
		case 7:{
			
			n = 15;
			break;
		}
		case 8:{
			
			n = 17;
			break;
		}
		case 9:{
			
			n = 19;
			break;
		}
		case 10:{
			
			n = 21;
			break;
		}
		default:{
			
			n = 0;
			break;
		}
	}
	
	return n;
}


// elimina le navi indovinate
void affondaNave( tab **ptesta, int num, int x, int y ){
	
	tab *ptemp = (*ptesta);
	
	int i, j;

    //controlla chi ha colpito la nave
	if ( num = 1 ){
		
		ptemp = ptemp->pnext;
		
	} else {
		
		ptemp = (*ptesta);
	}
	
	int len = 0, t = 0;
	
	char s;
	
	if ( ptemp->campo[x][y] != 'X' || ptemp->campo[x][y] != 'O' ){
		
		ptemp->campo[x][y] = 'X';
		
		s = ptemp->cont[x][y];
		
		for( i = 3; i < r; i++ ){
			for( j = 3; j < c; j++ ){
						
				if( ptemp->cont[i][j] == s ){
					
					len++;
					
					if( ptemp->campo[i][j] == 'X' ){
						
						t++;
					}
					
				}
			}
		}
		
		if ( len == t ){
			
			printf("\nUna nave e' stata abbattuta");
			
			ptemp->nv--;
		}
		
	} else {
		
		printf("\nCella gia selezionata");
	}
}


// estrae l'input per generare coordinate giocatore
void giocatore( tab **ptesta ){
	
	tab *ptemp = (*ptesta);
	
	ptemp = ptemp->pnext;
	
	int x = 0, y = 0;
	
	char xx;
	
	printf("\n\t\t\t\t\t Inserisci Le coordinate delle lettere es.[A]: ");
	printf("\n\t\t\t\t\t -> ");
    scanf(" %c",&xx);
    
    printf("\n\t\t\t\t\t Inserisci Le coordinate numeriche es.[9]: ");
    printf("\n\t\t\t\t\t -> ");
    scanf("%d",&y);
    
    xx = tolower(xx);
	
	// parametrizzo il carattere yy in intero
	switch ( xx ){
		
		case 'a':{
			
			x = 3;
			break;
		}
		case 'b':{
			
			x = 5;
			break;
		}
		case 'c':{
			
			x = 7;
			break;
		}
		case 'd':{
			
			x = 9;
			break;
		}
		case 'e':{
			
			x = 11;
			break;
		}
		case 'f':{
			
			x = 13;
			break;
		}
		case 'g':{
			
			x = 15;
			break;
		}
		case 'h':{
			
			x = 17;
			break;
		}
		case 'i':{
			
			x = 19;
			break;
		}
		case 'j':{
			
			x = 21;
			break;
		}
		default:{
			
			printf("\nLa coordinata y non ha senso");
			break;
		}
	}
	
	int ver = parametrizza( y );
	
	if( ver != 0 ){
		
		y = ver;
		
		if ( ptemp->campo[x][y] != ' ' ){
			
			printf("\nHai colpito una nave");
			
			int n = 0; // stato giocatore
		
			affondaNave( ptesta, n, x, y );
			
		} else {
			
			printf("\nColpo a vuoto :(");
			
			ptemp->campo[x][y] = 'O';
		}
			
	} else {
		
		printf("\ninserisci delle coordinate sensate se vuoi vincere >:(");
	}
}


// genera numeri casuali per le coordinate cpu
void cpu( tab **ptesta ){
	
	tab *ptemp = (*ptesta);
	
	int n1 = rand() % 10;
	int n2 = rand() % 10;
	
	const int xx[10] = { 3,5,7,9,11,13,15,17,19,21 };
	const int yy[10] = { 3,5,7,9,11,13,15,17,19,21 };
	
	int x = xx[n1], y = yy[n2];
	
	if ( ptemp->campo[x][y] != ' ' ){
		
		printf("\nLa cpu ti ha colpito VENDICATI!!");
		
		int n = 1;// stato giocatore
		
		affondaNave( ptesta, n, x, y );
		
	} else {
		
		printf("\nEi guarda che la cpu ha provato ha colpirti VINCI PER NOI!!");
		
		ptemp->campo[x][y] = 'O';
	}
}


// inizializza il gioco
int gioco( int pin ){

    tab *ptesta = NULL;
    
    int n = 2; // numero di campi da generare
	
	campoGioco( &ptesta, n );
	
	tab *ptemp = ptesta;
    
    printf("\nGioca!! ");
    
    int i = 0, j;
    
    char str[r];
    
    int esito, finito;
	
	do{ // chiedo l'input e controllo che la partita non sia terminate
	
		// stampo il campo del giocatore
		printf("\n\n");
		printf("\t\t\t\t\t\t\tIl tuo campo\n");
	    for( i = 0; i < r; i++ ){
	    	
	    	printf("\t\t\t\t\t\t");
	    	for( j = 0; j < c; j++ ){
	    		
	    		printf("%c", ptemp->campo[i][j]);
			}
			printf("\n");
		}
		
		if ( pin == 2757 ){
			
			ptemp = ptemp->pnext;
			
			for( i = 0; i < r; i++ ){
	    	
		    	printf("\t\t\t\t\t\t");
		    	for( j = 0; j < c; j++ ){
		    		
		    		printf("%c", ptemp->campo[i][j]);
				}
				printf("\n");
			}
		}
		ptemp = ptesta;
		
		// prendo le coordinate
		printf("\n\t\t\t\t\til tuo Campo ha %d navi", ptemp->nv);
		ptemp = ptemp->pnext;
		printf("\n\t\t\t\t\tIl campo della cpu ha %d navi", ptemp->nv);
    
    	giocatore( &ptesta );// richiamo funzione giocatore
    	
    	cpu( &ptesta ); // richiamo funzione cpu
    	
    	ptemp = ptesta;
    	
    	tab *ptemp2 = ptemp->pnext;
    	
    	if ( ptemp->nv == 0 ){ // controllo chi ha vinto la partita
    		
    		printf("\nLa cpu ha vinto addio");
    		
    		esito = 1;
    		
    		finito = 0;
    		
    		score++;
    		
    		strcpy( str, "cpu");
		
		} else if ( ptemp2->nv == 0 ){
			
			printf("\nhai vinto addio");
			
			esito = 0;
			
			finito = 0;
			
			score++;
			fflush(stdin);
			gets(str);
		}
		
	}while( finito );
	
	FILE *pfile = fopen( "score.txt","w+" );
    	
    i = 0;
	
	if( pfile != NULL ){// controllo che il file esista
    	
    	tab *ptemp2 = ptemp->pnext;                    
	
		ptemp = ptesta;
	
		part *pTesta = NULL;
    	
    	part *pTemp = NULL;
			
		while( i != score ){
		
			pTemp = (part*)malloc(sizeof(part)); // Allocazione di un nuovo nodo
			
			strcpy( pTemp->vincitore, str );
			
			pTemp->nvC = ptemp2->nv; // assegno il numero di navi
			pTemp->nvG = ptemp->nv; // assegno il numero di navi
			
			fprintf( pfile, "\nVincitore: %s", pTemp->vincitore );
			fprintf( pfile, "\nNavi rimaste alla cpu: %d", pTemp->nvC );
			fprintf( pfile, "\nNavi rimaste al giocatore: %d", pTemp->nvG );
			
			pTemp->pnext = pTesta;
			
			pTesta = pTemp;
			
			i++;
		}
		
		fclose (pfile);
	}
	
	return esito;
}


// stampa un messaggio
void addio(){
	
	int i;
	
	char frase[DIM]={'A','d','d','i','o',' ',':','('};
	
	printf("\n");
	
	for ( i = 0; i < 10; i++ ){
		
		printf("%c",frase[i]);
	}
}


// menu del gioco
void menu(){
	
	// memorizza la scelta dell'utente
	int s;

    tab campo[r];
	
	/*
    int n;

	printf("\nQuanti giocatori siete? ");
    printf("\n-> ");
    scanf("%d",&n);
    */

    printf("\nCampi generato");
    
    do {
    	
    	printf("\nCiao, Benvenuto a battaglia navale!!\n");
		printf("\n1 - Gioca!!");
		printf("\n2 - Score ");
		if ( score == 0 ){ printf(" ( Non disponibile )"); }
		printf("\n3 - Visualizza campo cpu");
	    printf("\n4 - Riavvio");
		printf("\n5 - esci");
		printf("\n-> ");
		scanf("%d",&s);
		
		switch (s){
			
			case 1:{
				
				int pin = 0;
				
		        int num = gioco( pin );
		        
		        //salva( ptesta, num );
		        break;
		    }
			case 2:{
				
				if ( score == 0 ){
					
					printf("\n( Non disponibile )\n"); 
				
				} else {
					
					printf("Cerca un file di nome score in cui ci sono salvate le vecchie partite");
				}
				
		        break;
		    }
		    case 3:{
		    	
		        int pin = 0;
		        
		        printf("\nInserisci pin\n-> ");
		        scanf("%d",&pin);
				
		        int num = gioco( pin );
		        break;
		    }
			case 4:{
				
		        printf("\nRiavvio effettuato");
		        break;
		    }
		    case 5:{
				
		        addio();
		        break;
		    }
			default:{
				
				printf("\nERRORE Commando non riconosciuto");
				break;
			}
		}
		
	}while ( s != 4 );
}


// funzione principale
int main(){
	
	srand(time(NULL));
	
	menu();
	
	return 0;
}