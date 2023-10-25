/*
	Nome: Two Sum
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


int* twoSum( int* nums, int numsSize, int target, int* returnSize ){
	
    int i, j;

    for ( i = 0; i < numsSize; i++ ) {
        for ( j = i + 1; j < numsSize; j++ ) {
        	
            if ( nums[i] + nums[j] == target ) {
            	
                int* result = (int*)malloc(2 * sizeof(int));
                
                result[0] = i;
                result[1] = j;
                
                *returnSize = 2;
                
                return result;
            }
        }
    }

    *returnSize = 0; // No coupple founded
    return NULL;
}


int main() {
	
    int arr[] = {2, 7, 11, 15};
    int Size = 4;
    int target = 9;
    int returnSize = 0;
    int* retur = twoSum(arr, Size, target, &returnSize);

    if (returnSize == 2) {
    	
        printf("[%d, %d]\n", retur[0], retur[1]);
        free(retur);
        
    } else {
    	
        printf("No coupple founded\n");
    }

    return 0;
}