#include <stdlib.h>
#include <stdio.h>
#include "arrayinttostring.h"


intStringPairArray intStringPairArray_new(size_t size){
	intStringPairArray newArr;
	int attempts = -1;
	
	newArr.size = 0;
	newArr.maxSize = size;
	newArr.values = NULL;
	if (size)
		while (newArr.values == NULL){
			if (++attempts == INTSTRINGPAIRARRAY_ALLOC_ATTEMPTS){
			/* tests 0 == maxAttempts on first pass, */
			/* 1 == maxAttempts on second pass, etc, */
			/* so we get the intended behavior */
				fprintf(stderr, "Couldn't allocate array.\n");
				exit(EXIT_FAILURE);
			}
			newArr.values = malloc(size * sizeof *newArr.values);
		}
	
	return newArr;
}

intStringPairArray intStringPairArray_append(
	intStringPairArray arr, intStringPair pair){
	
	if (arr.size == arr.maxSize){ /* need to expand array */
		
		intStringPair* res = NULL;
		int attempts = -1;
		
		if (arr.maxSize)
			arr.maxSize *= 2;
		else
			arr.maxSize = 1;
		
		while (res == NULL){
			if (++attempts == INTSTRINGPAIRARRAY_ALLOC_ATTEMPTS){
			/* tests 0 == maxAttempts on first pass, */
			/* 1 == maxAttempts on second pass, etc, */
			/* so we get the intended behavior */
				fprintf(stderr,
					"Couldn't re-allocate array.\n");
				exit(EXIT_FAILURE);
			}
			res = realloc(arr.values, arr.maxSize * sizeof *res);
		}
		arr.values = res;
	}
	
	arr.values[arr.size++] = pair;
	
	return arr;
}
