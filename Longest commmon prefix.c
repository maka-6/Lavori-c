/*
	Nome: Longest common prefix
	Copyright: xx
	Autore: Youness Makaoui
	Luogo: Home
	Versione: xx
	Componenti: xx
	Data: xx
	Descrizione:
 		- soluzione problema n. 14 Longest Common Prefix su leetcode
*/

#include <stdlib.h>
#include <string.h>


// Leetcoode problem solution
char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize < 1) {
        return NULL;  // No common prefix for an empty array
    }

    int prefixLen = strlen(strs[0]);
    char* prefix = (char*)malloc((prefixLen + 1) * sizeof(char));

    // Copy the first string to the prefix
    strcpy(prefix, strs[0]);

    for (int i = 1; i < strsSize; ++i) {
        int j = 0;
        while (strs[i][j] && prefix[j] == strs[i][j]) {
            ++j;
        }
        prefix[j] = '\0';  // Null-terminate the prefix at the mismatch point
    }

    return prefix;
}
