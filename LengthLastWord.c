#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLastWord(char * s) {

    int l = 0, i = 0, j;

    while( i < strlen(s) ){

        if( s[i] == ' ' ){
            i++;

        } else {

            l = 0;
            j = i;
            while( s[j] != ' ' && j < strlen(s) ){

                j++;
                l++;
            }
            i = j;
        }
    }

    return l;
}

int main(){

    char *s = " Hello World ";

    int n = lengthOfLastWord( s );

    printf("\nLength: %d",n);
    printf("\nS length: %d", strlen(s));

    exit(0);
}