#ifndef arrayinttostring_h_included
#define arrayinttostring_h_included


#define INTSTRINGPAIRARRAY_ALLOC_ATTEMPTS 4


typedef struct {
	int i;
	char* s;
} intStringPair;

typedef struct {
	size_t size;
	size_t maxSize;
	intStringPair* values;
} intStringPairArray;


intStringPairArray intStringPairArray_new(size_t size);

intStringPairArray intStringPairArray_append(
	intStringPairArray arr, intStringPair pair);


#endif /* arrayinttostring_h_included */
