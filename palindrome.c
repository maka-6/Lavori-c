/*
	Nome: palindrome
	Copyright:
	Autore:
	Luogo:
	Versione:
	Componenti:
	Data:
	Descrizione:
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
bool isPalindrome( int x ){

    int len = 0;
    int xs = x;

    while( xs != 0 ){
      xs/=10;
      len++;
    }

    char str[len];
    snprintf( str, sizeof(str), "%d", x );

    if ( str[0] == str[len-1] ){
    	
    	printf("\nS");

      	return true;
      
    } else {
    	
    	printf("\nN");
		return false;
    }
}
*/

bool isPalindrome( int x ){

    int len = 0;
    int xs = x;

    long long reversed = 0;

    while (xs != 0) {
        reversed *= 10 + xs % 10;
        xs /= 10;
    }
    printf("%d",x);
}


int main(){
	
	int x;
	
	scanf("%d",&x);
	
	isPalindrome( x );
	
	return 0;
}
