#ifndef UTILITY_HEADER
#define UTILITY_HEADER

#include <stdbool.h>

#include "graph.h"

typedef struct _data{
	unsigned int node;
	double distance;
	unsigned int from;
}data;

typedef struct _Heap{
	unsigned int size;
	unsigned int last;
	data* heap;
}Heap;


Heap* pQueueInit(unsigned int size);
int pop(Heap* heap,data* toSet);
int addQueue(Heap* Heap,int node, int distance,int from)__attribute__((nonnull));
int popAndReplace(Heap* heap,int node,int distance,data* rtn)__attribute__((nonnull));
void printHeap(Heap* heap);

bool static inline isEmpty(Heap* heap)
{
	return heap -> last == 1;
}


void static inline emptyQueue(Heap* heap)
{
	heap -> last = 1;
}

#endif
