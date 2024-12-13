/*
	Nome: Negozio gamestop
	Versione: 1.2
	Copyright: nessuno
	Autore:
		-makaoui youness
	Classe: 3E
	Luogo: 
	Data: 06/05/23
	Descrizione:
		-Il programma simula un negozio del gamestop
*/

#include <stdio.h>
#include "Log-in.c"

#define r 50
#define d 1000


// struct di un prodotto
typedef struct{

    char name[r];// nome del prodotto
    char des[d];// descrizione prodotto
    char cat;// tipo di prodotto
    char com;// compatibilita del prodotto (solo con i videogiochi)
    char val[r];//valutazione del prodotto
    float price;
    int copy;
}Pr;


// conta il numero dei prodotti presenti
int n = 0;


// carica il file dentro un record
int load ( Pr prod[] ){

    FILE *pointFile = fopen("catalogo.txt", "r");

    if (pointFile != NULL ){

        while ( !feof(pointFile) ){

            fgets(prod[n].name, r, pointFile );
            fgets(prod[n].des, r, pointFile );
            fgets(prod[n].val, r, pointFile );
            fscanf(pointFile, " %c", &prod[n].cat );
            
            if ( prod[n].cat == 'v' ){// cerca la categoria v ( videogiochi ) ed estrae la compatibilita del gioco
            	
            	fscanf(pointFile, " %c", &prod[n].com );
			}
			else{
				fprintf(pointFile, "\n" );
			}
            fscanf(pointFile, "%f", &prod[n].price );
            fscanf(pointFile, "%d\n\n", &prod[n].copy );
            
            n++;
        }
        
        fclose(pointFile );

        return 0;

    }else{

        return -1;
    }
}


void catalogo( Pr prod[], char t, char v ){
	
	int i;
	
	for(i = 0; i < n; i++){
		
		if ( prod[i].cat == 'v' && prod[i].com == v ){
			
			printf("%d",t);
		}
	}
	
}


// mostra i vari prodotti del Gamestop
void prodotti ( Pr prod[] ){
	
	int i;
	
	int s;
	
	char t;
	
	printf("\n1 - Giochi per la tua console");
	printf("\n2 - Le nostre Action figure");
	printf("\n3 - Carte pokemon");
	printf("\n-> ");
	scanf("%d",&s);
	
	switch ( s ){
		
		case 1:{
			
			char v;
			
			printf("\nGiochi per Playstation: [p]");
		    printf("\nGiochi per Xbox: [x]");
		    printf("\nGiochi per pc: [w]");
		    printf("\nGiochi nintendo: [n]");
		    printf("\n-> ");
		    scanf(" %c",&v);
		    
		    t = 'v';
		    
		    catalogo( prod, t, v );
			break;
		}
		case 2:{
			
			t = 'a';
			
			catalogo( prod, t, t);
			break;
		}
		case 3:{
			
			t = 'k';
			
			catalogo( prod, t, t);
			break;
		}
		default:{
			
			printf("Errore, commando non riconosciuto");
			break;
		}
	}
}


int main(){

    int s;
    
    char t;

    Pr prod[r];

    LoginMain();
    
    int num = load ( prod );
    
    if ( num != -1 ){
    	
    	printf("\nBenvenuto al negozio del Gamestop!!");

        do{
        	
        	printf("\n");
            printf("\n1 - Tutti i nostri prodotti");
            printf("\n2 - catalogo dei vari prodotti");
            printf("\n3 - Riavvio");
            printf("\n4 - Esci");
            printf("\n-> ");
            scanf("%d",&s);
            printf("\n");

            switch ( s ){

                case 1:{
                	
                	t = ' ';
                	
                    catalogo( prod, t, t );
                    break;
                }
                case 2:{
                	
                    prodotti( prod );
                    break;
                }
                case 3:{

                    printf("\nRiavvio effettuato");
                    break;
                }
                case 4:{

                    printf("\nAddio");
                    break;
                }
                default:{

                    printf("Errore, commando non riconosciuto");
                    break;
                }
            }

        }while ( s != 4 );
    } else {
        printf("\nErrore!!");
    }
}