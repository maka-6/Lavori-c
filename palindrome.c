/*
	Nome: palindrome
	Copyright: xx
	Autore: Makaoui Youness
	Luogo: xx
	Versione: xx
	Componenti: xx
	Data: xx
	Descrizione: Soluzione problema n. 9. Palindrome Number su leetcode
*/

#include <stdlib.h>
#include <stdbool.h>

bool isPalindrome( int x ){

  if( x < 0 ){
    return false;
  }

  long reversed = 0;
  int xs = x;

  while (xs != 0) {
    reversed = reversed * 10 + xs % 10;
    xs /= 10;
  }

  return (x == reversed);
}
