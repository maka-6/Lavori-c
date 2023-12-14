/*
	Nome: QuickSort
	Copyright:
	Autore: Youness Makaoui
	Luogo:
	Versione:
	Componenti:
	Data:
	Descrizione:
*/

#include <stdio.h>


void swap( int *a, int *b ){
	
	int t;
	
	t = *a;
	*a = *b;
	*b = t;
}


int partition( int arr[], int low, int high ){
	
	int piv = arr[high];
	
	int i = low - 1;

    for ( int j = low; j <= high - 1; j++ ){
    	
        if ( arr[j] <= piv ){
        	
            i++;
            swap( &arr[i], &arr[j] );
        }
    }
    
    swap( &arr[i + 1], &arr[high] );

    return (i + 1);
}


void quickSort( int arr[], int i, int j ){
	
	if( i < j ){
		
		int piv = partition( arr, i, j );
		
		quickSort( arr, i, piv - 1 );
		quickSort( arr, piv + 1, j );
	}
}


int main(){
	
	int arr[] = { 40, 57, 6, 7, 5, 3, 9, 10, 91, 6 };
	int n;
	char s;
	int size = 9;
	
	printf("\n\nArray non ordinato: ");
	printf("\narr[");
	for( int j = 0; j < size; j++ ){
		
		printf(" %d ",arr[j]);
	}
	printf("]");
	
	quickSort( arr, 0, size-1 );
	
	printf("\n\nArray ordinato: ");
	printf("\narr[");
	for( int i = 0; i < size; i++ ){
		
		printf(" %d ",arr[i]);
	}
	printf("]");
	
	return 0;
}