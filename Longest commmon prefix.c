/*
	Nome: Longest commmon prefix
	Copyright: xx
	Autore: Youness Makaoui
	Luogo:
	Versione:
	Componenti:
	Data:
	Descrizione:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * longestCommonPrefix( char ** strs, int strsSize ){

    int i, min, max;
    
    for( i = 0; i < strsSize-1; i++ ){

        max = strlen( strs[i] );
        min = strlen( strs[i+1] );
        if( max < min ){
            max = min;
        }
    }int i, min, max;
    
    for( i = 0; i < strsSize-1; i++ ){

        max = strlen( strs[i] );
        min = strlen( strs[i+1] );
        if( max < min ){
            max = min;
        }
    }

    char prefix[min];
    strcpy( prefix, """" );
    char foundF;
    i = 0;
    int n = 0;

    for( i = 0; i < strsSize; i++ ){
        foundF = strs[0][i];
        for( int j = 0; j < min-1; j++ ){
            
            if( (strstr( strs[j+1], foundF )) != NULL ){
                n++;
            }
        }
    }

    if( n == strsSize ){

        n = 0;
        for( i = 0; i < strsSize; i++ ){

            if( (strstr( strs[i], prefix )) != NULL ){
                n++;
            }
        }
        
        if( n == strsSize ){
			
			
		}
    }

    return prefix;
}

int main(){
	
	
	
	exit (0);
}
