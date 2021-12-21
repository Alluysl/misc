#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arrayinttostring.h"

#define PAIRS_FILE_PATH "pairs.txt"

/* Rules of the game:
   Count from 1 to the specified value (user input)
   If the value is a multiple of 3 say Fizz, of 5 say Buzz,
   of 15 say FizzBuzz, else say the number */

#define ERROR_HANDLING_PAIR_FILE \
	{ perror("Error handling pairs file");\
	exit(EXIT_FAILURE); }

char* read_line(FILE* f){
	
	int size = -1;
	char* res;
	
	/* Get the size of the line */
	while (size <= 0){
		fpos_t pos;
		int c;
		
		/* Save the position of the descriptor */
		if (fgetpos(f, &pos))
			ERROR_HANDLING_PAIR_FILE
		
		do {
			++size;
			c = fgetc(f);
		} while (c != EOF && c != '\n');
		
		if (!size){
			
			if (c == EOF)
			/* reached end of file at beginning */
			/* of line, nothing to read anymore */
				return NULL;
			size = -1; /* skip empty lines */
			
		} else if (fsetpos(f, &pos))
			/* restore the position of the */
			/* descriptor if we keep going */
			ERROR_HANDLING_PAIR_FILE
	}
	
	++size; /* amount of characters to size of string */
	
	/* Allocate the memory for the string */
	/* sizeof(char) == 1 by definition */
	if ((res = malloc(size)) == NULL){
		fprintf(stderr, "Couldn't allocate memory for string.\n");
		exit(EXIT_FAILURE);
	}
	
	if (fgets(res, size, f) == NULL)
	/* happens when an error occurs or when no characters */
	/* were read but we're expecting at least one character */
		ERROR_HANDLING_PAIR_FILE
	
	{ /* remove newline (and carriage return on Windows) if was read */
		char* nl;
		
		if ((nl = strrchr(res, '\n')) != NULL)
			*nl = '\0';

#if defined(_WIN32) || defined(_WIN64)
		if ((nl = strrchr(res, '\r')) != NULL)
			*nl = '\0';
#endif
		
	}
	
	return res;
}

intStringPair get_pair_from_line(char* line){
	
	intStringPair pair;
	int sscanfRet;
	
	/* Get value */
	if ((sscanfRet = sscanf(line, "%d", &pair.i)) != 1
			|| strchr(line, ' ') == NULL){
		fprintf(stderr, "Couldn't parse line \"%s\".\n", line);
		if (sscanfRet == EOF)
			perror("The encountered error was");
		exit(EXIT_FAILURE);
	}
	
	/* Shift the string */
	{
		int i,
		    diff; /* index of the substring to bring */
			/* to the beginning of the string */
		
		for (diff = 0; line[diff] != ' '; ++diff);
		
		++diff;
		
		for (i = 0; line[i + diff] != '\0'; ++i)
			line[i] = line[i + diff];
		
		line[i] = '\0';
	}
	
	pair.s = line;
	
	return pair;
}

intStringPairArray get_pairs(
	intStringPairArray arr, const char* pairsFilePath){
	
	FILE* f = fopen(pairsFilePath, "rb");
	char* readLine;
	
	if (f == NULL){
		perror("Couldn't open pair file");
		exit(EXIT_FAILURE);
	}
	
	while ((readLine = read_line(f)) != NULL){
		arr = intStringPairArray_append(
			arr, get_pair_from_line(readLine));
		/* The line is freed at the end of execution */
	}
	
	fclose(f);
	
	return arr;
}

int check_print_special(int counter, int modulo, const char* name){
	
	if (!modulo || counter % modulo)
		return 0;
	
	printf("%s", name);
	return 1;
}

int main(){
	int n; /* upper bound to count to */
	int i; /* counter */
	
	intStringPairArray specialValues = get_pairs(intStringPairArray_new(2), PAIRS_FILE_PATH);
	
	printf("Number to count to: ");
	while (fflush(stdout), /* make sure the line before is printed */
		scanf(" %d", &n) != 1 || n < 1){ /* get bound from stdin */
		
		printf("Wrong number %d provided, should be 1 or above "
			"(15 or above recommended). Try again: ", n);
	}
	
	for (i = 1; i <= n; ++i){
		
		char special = 0; /* whether the value is "special" */
			/* (doesn't show the number but text instead) */
	    	int j;
	    	
	    	for (j = 0; j < (int)specialValues.size; ++j){
	    		
			special |= check_print_special(i,
				specialValues.values[j].i,
				specialValues.values[j].s);
			
			if (i == n) /* last pass */
				/* free allocated memory */
				free(specialValues.values[j].s);
		}
		
		if (special) /* text already shown... */
			printf("\n"); /* ... so just new line */
		else /* no text shown... */
			printf("%d\n", i); /* ... print value and new line */
	}
	
	
	free(specialValues.values); /* free allocated memory */
	
	return 0;
}
