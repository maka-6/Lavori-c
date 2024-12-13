/*
	Nome: i Ladri del Gamestop 
	Copyright: mekaui
	Versione: 1.5
	Autore: 
		- MAKAOUI YOUNESS
		- GHEZZI FEDERICO
		- VENEGONI DAVIDE
		
	Data: 10/05/23
	Description: 
		-Il programma simula un negozio di Gamestop
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define r 100
#define d 1000


//struct di un singolo prodotto
typedef struct{

    char name[r];// nome prodotto
    char des[d];// descrizione prodotto
    char val[r];// valutazione prodotto
    char cat;// categoria prodotto
    char com;// compatibilita prodotto
    float price;// prezzo del prodotto
    int copy;// copie disponibili del prodotto
    
}Pr;


//sruct del carrello
typedef struct{
	
	Pr prod;
	
}Carrello;


struct credenziali{
	
	char name[r];
	char password[r];
	
};


typedef struct{
	
	struct credenziali User;
	Carrello carre[d];
	
}user;


//conta il numero dei prodotti presenti
int n = 0;


// contiene il numero di prodotti nel carrello
int n2 = 0;


//carica il file dentro l'array di struct
int load ( Pr prod[] ){

    FILE *pfile = fopen("catalogo.txt","r+");

    if ( pfile != NULL ){//se trovo il file lo leggo
    	
    	printf("\nRicerca file...");

        while ( !feof(pfile) ){//lo leggo finche non fisnisce il file
        	
        	fgets( prod[n].name, r, pfile );
        	fflush(stdin);
        	strlwr( prod[n].name );//imposta la stringa in minuscolo
        	fgets( prod[n].des, r, pfile );
        	fflush(stdin);
        	strlwr( prod[n].des );
        	fgets( prod[n].val, r, pfile );
        	fflush(stdin);
        	strlwr( prod[n].val );
        	fscanf( pfile, " %c", &prod[n].cat );
        	fflush(stdin);
        	
        	if ( prod[n].cat == 'v' ){
        		
        		fscanf( pfile, " %c", &prod[n].com );
			}
			fscanf( pfile, "%f", &prod[n].price );
			fflush(stdin);
			fscanf( pfile, "%d\n", &prod[n].copy );
			fflush(stdin);
			n++;
        }
        
        fclose( pfile );
        
        return 0;

    }else{

        return -1;
    }
}


//ricerca un prodotto voluto dall'utente
int barraRicerca ( Pr product[] , int arr[], Carrello carr[], int h ){
	
	int i, num = 0, t = 0;
	
	char *ind;
	
	char str[r];
	
	printf("\n");
	
	if ( h > 0 ){
		
		for(i = 0; i < h; i++){
			
			printf("\n\n");
			printf("%d",t + 1);
			printf("\n Indice numerico: %d",i);
			printf("\n Nome: %s", product[i].name);
			printf(" Descrizione: %s", product[i].des);
			printf(" Valutazione: %s", product[i].val);
			printf(" Prezzo: %0.2f", product[i].price);
			printf("\n Copie disponibili: %d", product[i].copy);
			t++;
		}
	}
	
	printf("\n");
	
	t = 0;
	
	printf("\nScrivi il nome di un prodotto: ");
	fflush(stdin);
	gets(str);
	fflush(stdin);
	
	for(i = 0; i < n; i++){
		
		ind = strstr( product[i].name, str );
		
		if( ind != NULL ){//vedo se la parola chiave e contenuta in un prodotto
			
			printf("\n\n");
			printf("%d",t + 1);
			printf("\n Indice numerico: %d",i);
			printf("\n Nome: %s", product[i].name);
			printf(" Descrizione: %s", product[i].des);
			printf(" Valutazione: %s", product[i].val);
			printf(" Prezzo: %0.2f", product[i].price);
			printf("\n Copie disponibili: %d", product[i].copy);
			t++;
			
			num++;
		}
	}
	
	printf("\n\n%d - prodotti trovatti", num);
	
	return num;
}


//simula l'aquisto di un prodotto
void acquista ( Pr product[], Carrello carr[], Pr prod[], int *credit, int h ){
	
    int in, nc, num, i = 0, j;
    
    int arr[r];
    
    memset( arr, 0, sizeof(arr) );//inizializza l'array a zero
    
    char s;    
    
	do {//ciclo che conta e aggiunge al carrello i prodotti voluti
		
		num = barraRicerca( product, arr, carr, h );
	    	
    	if ( num > 0 ) {
    	
	        printf("\n\nSeleziona un prodotto inserendo il suo indice numerico: ");
	        scanf("%d", &in);
	        fflush(stdin);
	        
	        // Aggiungi questa verifica per assicurarti che l'indice selezionato sia valido
	            
	        if ( product[in].cat != ' ' ) {//controloo che ci sia un prodotto
	        	
	            printf("\nQuante copie desidera: ");
	            scanf("%d", &nc);
	            fflush(stdin);
	            
	            int v = nc*product[in].price;
	            
	            if ( *credit >= v ){//controlla che l'acquisto non superi il credito disponibile
	            	
	            	*credit = *credit - v;//decrementa il credito
	            
		            if ( product[in].copy >= nc ) {//se il numero richiesto di copie supera la disponibilita stampo errore
		            	
		            	product[in].copy -= nc;
		                
		                for ( j = 0; j < n; j++ ) {//cerca il prodotto originale e decrementa il numero di copie
		                	
		                    int com = strcmp( prod[j].name, product[in].name );//cerco la parola chiave nel nome del prodotto
		                    
		                    if ( com == 0 ) {
		                    	
		                        prod[j].copy -= nc; // Modifica il numero di copie nel catalogo originale
		                    }
		                }
		                
		                carr[i].prod = product[in];
		                carr[i].prod.copy = 0;
		                carr[i].prod.copy += nc;
		                
		                n2++;
			        }
		            else {
		                printf("\nCopie insufficienti");
		            }
				}else{
			    	
			    	printf("\nNon hai soldi poveraccio, come back to home");
				}
	        }
	        else {
	            printf("\nProdotto non trovato");
	        }
	        
	        printf("\nVuoi comprare altro [y/n]?: ");
	        scanf(" %c", &s);
	        fflush(stdin);
	        i++;
		        
		}
	        
	} while (s != 'n');
}


//stampa tutto il catalogo del negozio
void catalogo ( Pr prod[] ){
	
	int i, t = 0;
	
	for (i = 0; i < n; i++ ){//stampo il catalogo
		
		printf("\n\n");
		printf("%d",t + 1);
		printf("\n Nome: %s", prod[i].name);
		printf(" Descrizione: %s", prod[i].des);
		printf(" Valutazione: %s", prod[i].val);
		printf(" Prezzo: %0.2f", prod[i].price);
		printf("\n Copie disponibili: %d", prod[i].copy);
		t++;
	}
}


//stampa i vari prodotti scelti dall'utente
void prodotti ( Pr prod[], Carrello carr[], int *credit ){
	
	int i, t = 0, h = 0;
	
	char s;
	
	int v, num, bool = 0;
	
	//memorizza la categoria scelta e ne manipola il numero di copie
	Pr product[r];
	
	printf("\n1 - Videogiochi");
	printf("\n2 - Action Figure");
	printf("\n3 - Carte Pokemon");
	printf("\n: ");
	scanf("%d",&v);
	fflush(stdin);
	
		
	switch ( v ){//switch che filtra le categorie
		
		case 1:{
			
			for(i = 0; i < n; i++){
				
				if ( prod[i].cat == 'v' ){
					
					product[i] = prod[i];
					
					bool = 1;
					
					h++; // numero di prodotti caricati
				}
			}
			
			if ( bool == 1 ){
				
				acquista( product, carr, prod, credit, h );
			}
			
			break;
		}
		
		case 2:{
			
			for(i = 0; i < n; i++){
				
				if ( prod[i].cat == 'a' ){
					
					product[i] = prod[i];
					
					bool = 1;
					
					h++; // numero di prodotti caricati
				}
			}
			
			if ( bool == 1 ){
				
				acquista( product, carr, prod, credit, h );
			}
			
			break;
		}
		
		case 3:{
			
			for(i = 0; i < n; i++){
				
				if ( prod[i].cat == 'k' ){
					
					product[i] = prod[i];
					
					bool = 1;
					
					h++; // numero di prodotti caricati
				}
			}
			
			if ( bool == 1 ){
				
				acquista( product, carr, prod, credit, h );
			}
			
			break;
		}
		default:{
			
			printf("\nErrore, illegal command");
			break;
			break;
		}
	}
}


//stampa esclusivamente i giochi voluti dall'utente
void videogiochi ( Pr prod[], Carrello carr[], int *credit ){
	
	char v;
	
	int i, t = 0, bool = 0, h = 0;
	
	Pr product[r];
	
	printf("\n1 - PlayStation [ p ]");
	printf("\n2 - Xbox [ x ]");
	printf("\n3 - Nintendo [ n ]");
	printf("\n4 - Pc windows [ w ]");
	printf("\n-> ");
	scanf(" %c",&v);
	fflush(stdin);
		
	switch ( v ){//switch che filtra le categorie dei videogiochi
		
		case 'p':{//cerca e stampa i giochi play
			
			for(i = 0; i < n; i++){
			
				if ( prod[i].com == 'p' ){
					
					product[i] = prod[i];
					
					bool = 1;
					
					h++; // numero di prodotti caricati
				}
			}
			
			if ( bool == 1 ){
				
				acquista( product, carr, prod, credit, h );
			}
			break;
		}
		case 'x':{//cerca e stampa i giochi xbox
			
			for(i = 0; i < n; i++){
			
				if ( prod[i].com == 'x' ){
					
					product[i] = prod[i];
					
					bool = 1;
					
					h++; // numero di prodotti caricati
				}
			}
			
			if ( bool == 1 ){
				
				acquista( product, carr, prod, credit, h );
			}
			break;
		}
		case 'n':{//cerca e stampa i giochi nintendo
			
			for(i = 0; i < n; i++){
			
				if ( prod[i].com == 'n' ){
					
					product[i] = prod[i];
					
					bool = 1;
					
					h++; // numero di prodotti caricati
				}
			}
			
			if ( bool == 1 ){
				
				acquista( product, carr, prod, credit, h );
			}
			break;
		}
		case 'w':{//cerca e stampa i giochi windos
			
			for(i = 0; i < n; i++){
			
				if ( prod[i].cat == 'w' ){
					
					product[i] = prod[i];
					
					bool = 1;
					
					h++; // numero di prodotti caricati
				}
			}
			
			if ( bool == 1 ){
				
				acquista( product, carr, prod, credit, h );
			}
			break;
		}
		default:{
			
			printf("\nErrore, illegal command");
			break;
		}
	}
} 


//carrello cotente i prodotti
void carre ( Pr prod[], Carrello carr[], int *credit ){
	
	int i, t = 0;
	
	if ( n2 > 0 ){//se ci sono prodotti nel carrello li stampo
	
		printf("\n\nCredito residuo: %d", credit);
		
		printf("\n%d - Prodotti nel carrello", n2);
		
		for ( i = 0; i < n2; i++ ){
			
			printf("\n\n");
			printf("%d",t + 1);
			printf("\n Nome: %s", carr[i].prod.name);
			printf(" Descrizione: %s", carr[i].prod.des);
			printf(" Valutazione: %s", carr[i].prod.val);
			printf(" Prezzo: %0.2f", carr[i].prod.price);
			printf("\n Copie disponibili: %d", carr[i].prod.copy);
			t++;
		}
	}
	else{
		
		printf("\nCarrello vuoto :(");
	}
}


void menu (){

	int s, h = 0;
    
    Pr prod[r];//catalogo dei prodotti
    
    int num = load ( prod );// carico il catalogo dal file
    
    Carrello carr[d];//creo il carrello
    
    int credit; // il credito del utente
    
    if ( num != -1 ){
    	
		printf("\nFile aperto con successo!!");
		
		printf("\nInserisci il tuo credito: ");
    	scanf("%d",&credit);
    	fflush(stdin);

        do{
        	
        	printf("\n\nCredito residuo: %d", credit);
        	printf("\n");
            printf("\n1 - Visualizza tutto il catalogo");
            printf("\n2 - Acquista un prodotto");
            printf("\n3 - Acquista un gioco per la tua console");
            printf("\n4 - Cerca un prodotto");
            printf("\n5 - Carrello");
            printf("\n6 - Riavvio");
            printf("\n7 - Esci");
            printf("\n-> ");
            scanf("%d",&s);
            printf("\n");

            switch ( s ){

                case 1:{

                    catalogo ( prod );
                    break;
                }
                case 2:{

                    prodotti ( prod, carr, &credit );
                    break;
                }
                case 3:{

                    videogiochi ( prod, carr, &credit );
                    break;
                }
                case 4:{
                	
                	acquista( prod, carr, prod, &credit, h );
					break;
				}
                case 5:{
                	
                	carre( prod, carr, &credit );
                    break;
                }
                case 6:{

                    printf("\nRiavvio effettuato");
                    break;
                }
                case 7:{

                    printf("\nAddio");
                    break;
                }
                default:{

                    printf("Errore, commando non riconosciuto");
                    break;
                }
            }

        }while ( s != 7 );
    }
    else{
    	
    	printf("\nFile non trovato ");
	}
}


void acess (){
	
	
	int s;
    printf("\n1 - Accedi");
    printf("\n2 - Registrati");
    printf("\n3 - Esci");
    printf("\n-> ");
    scanf("%d",&s);
    fflush(stdin);
    printf("\n");

    switch ( s ){

        case 1:{

            
            break;
        }
        case 2:{

            
            break;
        }
        case 3:{

            printf("\nAddio");
            break;
        }
        default:{

            printf("Errore, commando non riconosciuto");
            break;
        }
    }
}


int main (){
	
	
    
    exit(0);
}