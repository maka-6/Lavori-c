/*
	Autore: MAKAOUI YOUNESS
	Copyright: nessuno
	Data: xx
	Versione: 1.1 Beta
	Classe: 3E
	Luogo: xx
	Novita' versione:
		- 1.1:
			-ottimizzazione
			Ancora in revisione
	Descrizione:
			-il programma simula battaglia navale contro il computer
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>


#define r 23 // definisco 23 righe
#define c 23 // definisco 23 colonne
#define DIM 50 // dimensione degli array


// numero partite giocate
int score = 0;

// struct nave
typedef struct{
	
	int dim;// dimensione della nave
	
	// coordinate della nave
	int x;
	int y;
	
	int verso;// verso della nave
	
}oggetto;


// struct matrice
typedef struct tab{
	
	char campo[r][c]; // matrice del campo
	
	char cont[r][c]; // matrice indici navi
	
	int nv; // numero navi rimaste 
	
	struct tab *pnext;
	
}tab;


// stampa resoconto partita nel file
typedef struct part{
	
	char vincitore[r]; // nome del vincitore
	
	int nvG; // numero navi giocatore rimaste
	
	int nvC; // numero navi cpu rimaste
	
	struct part *pnext;
	
}part;


// genera il campo
void campoGioco( tab **ptesta, int s ){

	int i, j, g, l;
	
	tab *ptemp = NULL;
	
    printf("\nGenerazione del campo...");
    
    for( g = 0; g < s; g++ ){// genera i campi richiesti
    	
    	ptemp = (tab*) malloc(sizeof(tab)); // Allocazione di un nuovo nodo per ptemp

		// inizializza la matrice con carattere 0 ASCII
		memset( ptemp->campo, ' ', sizeof(ptemp->campo));
	
	    char lett = 'A', num = '1'; // convertono i numeri in caratteri num = numeri e lett = alfabetici
	    
	    
	    // scrivo lettere e numeri
		for ( i = 3; i < c - 1; i+=2 ){
			// assegno i numeri alle posizioni orizzontali
			ptemp->campo[1][i] = num;
			num++;
			
		    // assegno le lettere alle posizioni verticali
		    ptemp->campo[i][0] = lett;
		    lett++;
		}
		ptemp->campo[1][21] = 'X';// X sostituisce il 10 essendo una stringa
		
		
		// creo i bordi
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
		// creo gli angoli
		ptemp->campo[2][2] = 218;
		ptemp->campo[22][2] = 192;
		ptemp->campo[22][22] = 217;
		ptemp->campo[2][22] = 191;
	
		// array che contiene le navi
		oggetto item[14];
		
		char indice = 48;// indice univoco per ogni nave, parte da 0 = 48 in ASCII
	
		// numero di navi
		int nv = 0;

        // genero una matrice per gli indici
		for ( i = 0; i < r; i++ ){
			for ( j = 0; j < c; j++ ){
			
				ptemp->cont[i][j] = ptemp->campo[i][j];
			}
		}
	
	    printf("\nCreo le navi...");
	    
	    i = 0;
	    
	    // crea le navi nel campo
	    while( i < 13 ){
	    	
	    	// verifica che ci sia spazio per la nave
		    int v = 0;
		    
		    item[i].dim = rand() % 4 + 1; // dimensione da 1 a 4
		    item[i].verso = rand() % 2; // verso 1 o 0

            // array contenenti le celle vuote
		    const int arr[10] = { 3,5,7,9,11,13,15,17,19,21 };
		    
			// coordinate da 0 a 9
			int nx = rand() % 10; 
	    	int ny = rand() % 10;
	    	
	    	// coordinate di una nave
	    	item[i].x = arr[nx]; // assegno x
	    	item[i].y = arr[ny]; // assegno y

		    int x = item[i].x;
		    int y = item[i].y;
		    
		    // verifico che le celle siano vuote
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
				i++;
	        }
	        
	        v = 0;
	        
		}
		
		ptemp->nv = nv;
		
		ptemp->pnext = *ptesta;
		
		*ptesta = ptemp;
	}
    printf("\nGenerazione completata");
}


// elimina le navi indovinate
void affondaNave( tab *ptemp, int x, int y ){
	
	int i, j;
	
	int len = 0, t = 0;
	
	char s;
	
	if ( ptemp->campo[x][y] == 'X' || ptemp->campo[x][y] == 'O' ){
		
		printf("\nCella gia selezionata in precendenza");
			
	} else {
		
		ptemp->campo[x][y] = 'X';
		
		printf("\nHai colpito una nave");
		
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
	}
}


// estrae l'input per generare coordinate giocatore
void giocatore( tab **ptesta ){
	
	tab *ptemp = (*ptesta);
	
	ptemp = ptemp->pnext;
	
	int x = 3, y = 0, i;
	
	char xx;
	
	printf("\n\t\t\t\t\t Inserisci Le coordinate es.[A9]: ");
	printf("\n\t\t\t\t\t -> ");
    scanf(" %c",&xx);
    scanf("%d",&y);
    
    xx = tolower(xx);
	
	// parametrizzo il carattere yy in intero
	int diff =  xx - 97;
	for( i = 0; i < diff; i++ ){// aumenta il valore di x a seconda del valore di xx
		
		x+=2;
	}
	
	int n;
	
	if ( y > 0 && y < 11 ){
		n = ( y + y ) + 1;
		
	} else {
		printf("\nCoordinate non valide");
	}
	
	if( n != 0 ){
		
		y = n;
		
		if ( ptemp->campo[x][y] != ' ' ){
		
			affondaNave( ptemp, x, y );
			
		} else {
			
			printf("\nColpo a vuoto :(");
			
			ptemp->campo[x][y] = 'O';
		}
			
	} else {
		
		printf("\ninserisci delle coordinate sensate se vuoi vincere >:(");
	}
}


// genera numeri casuali per le coordinate cpu
void computer( tab **ptesta ){
	
	tab *ptemp = (*ptesta);
	
	int n1 = rand() % 10;
	int n2 = rand() % 10;
	
	const int xx[10] = { 3,5,7,9,11,13,15,17,19,21 };
	const int yy[10] = { 3,5,7,9,11,13,15,17,19,21 };
	
	int x = xx[n1], y = yy[n2];
	
	if ( ptemp->campo[x][y] != ' ' ){
		
		printf("\nIl computer ti ha colpito VENDICATI!!");
		
		affondaNave( ptemp, x, y );
		
	} else {
		
		printf("\nColpo a vuoto dal computer!!");
		
		ptemp->campo[x][y] = 'O';
	}
}


// salva i punteggi delle partite
int salva( tab *ptesta ){
	
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
    	fflush(stdin);
    	gets(str);
			
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
		
		num = 1;
		
	}
	
	return num;
}


// stampa un messagio
void stmp( int ver ){
	
	
	if ( ver == 1 ){
	
    	char str[2];
    	
    	printf("\nEz boy, ma ora dimmi visto che hai avuto il coraggio di finire una partita");
    	printf("\nDi che colore e' il sole?\n-> ");
    	scanf("%s",str);
    	
    	if( str[0] != ' ' ){
    		
    		printf("\nSbagliato ESCI DI CASA, tutti sanno che viola come me?? ?????giusto??????");
		}
		
	} else {
		
		printf("\nErrore nella creazione del file");
	}
}


// inizializza il gioco
int gioco( tab *ptesta ){
	
	campoGioco( &ptesta, 2 );
	
	tab *ptemp = ptesta;
    
    printf("\nGioca!! ");
    
    int i = 0, j;
    
    int fine = 0;
	
	do{ // loop game
	
		// stampo il campo del giocatore
		printf("\n\n");
		printf("\t\t\t\tIl tuo campo\n");
	    for( i = 0; i < r; i++ ){
	    	
	    	printf("\t\t\t\t");
	    	for( j = 0; j < c; j++ ){
	    		
	    		printf("%c", ptemp->campo[i][j]);
			}
			printf("\n");
		}
		
			
		ptemp = ptemp->pnext;
		
		for( i = 0; i < r; i++ ){
    	
	    	printf("\t\t\t\t\t\t");
	    	for( j = 0; j < c; j++ ){
	    		
	    		printf("%c", ptemp->campo[i][j]);
			}
			printf("\n");
		}
		ptemp = ptesta;
		
		// prendo le coordinate
		printf("\n\t\t\t\t\tHai %d navi rimaste", ptemp->nv);
		ptemp = ptemp->pnext;
		printf("\n\t\t\t\t\tIl computer ha %d navi rimaste", ptemp->nv);
    
    	giocatore( &ptesta );// richiamo funzione giocatore
    	
    	computer( &ptesta ); // richiamo funzione cpu
    	
    	ptemp = ptesta;
    	
    	tab *ptemp2 = ptemp->pnext;
    	
    	if ( ptemp->nv == 0 ){ // controllo chi ha vinto la partita
    		
    		printf("\nIl computer ha vinto addio NOOB");
    		
    		fine = 1;
    		
    		score++;
		
		} else if ( ptemp2->nv == 0 ){
			
			printf("\nhai vinto addio");
			
			fine = 1;
			
			score++;
		}
		
	}while( !fine );
	
	if ( fine ){
		
		int ver = salva( ptesta );
		
		stmp( ver );
	}
	
	printf("ADDIO PAZZOIDE");
	
	_sleep(1000);
	
	system("CLS");
	
	return 0;
}


// menu del gioco
void menu(){
	
	// memorizza la scelta dell'utente
	int s;

    tab campo[r];
	
	/*
	
		questo pezzo di codice fara pare della futura implementazione del multiplayer
    int n;

	printf("\nQuanti giocatori siete? ");
    printf("\n-> ");
    scanf("%d",&n);
    */
    
    tab *ptesta = NULL;
    
    int n = 2;
    
    do {
    	
    	printf("\nCiao, Benvenuto a battaglia navale!!\n");
		printf("\n1 - Gioca!!");
		if ( score != 0 ){ printf("\n2 - Score "); }
		printf("\n3 - Visualizza campo cpu");
	    printf("\n4 - Riavvio");
		printf("\n5 - esci");
		printf("\n-> ");
		scanf("%d",&s);
		
		switch (s){
			
			case 1:{
				
		        gioco( ptesta );
		        		        
		        break;
		    }
			case 2:{
				
				if ( score == 0 ){
					
					printf("\n( Non disponibile )\n"); 
				
				} else {
					
					//stampa( ptesta );
				}
				
		        break;
		    }
		    case 3:{
				
		        gioco( ptesta );
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