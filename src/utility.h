#ifndef UTILITY_HEADER
#define UTILITY_HEADER

#include <stdbool.h>

#include "graph.h"

typedef struct _data{
	unsigned int node;
	unsigned int distance;
	unsigned int from;
}data;

typedef struct _Heap{
	unsigned int size;
	unsigned int last;
	data* heap;
}Heap;


Heap* pQueueInit(unsigned int size);
void peak(Heap* heap,data* toSet);
void pop(Heap* heap,data* toSet);
void addQueue(Heap* Heap,unsigned int node, unsigned int distance,unsigned int from)__attribute__((nonnull));
void popAndReplace(Heap* heap,unsigned int node,unsigned int distance,unsigned int from)__attribute__((nonnull));
void printHeap(Heap* heap);
void popAndIgnore(Heap* heap);

static inline bool isEmpty(Heap* heap)
{
	return heap -> last == 1;
}


static inline void emptyQueue(Heap* heap)
{
	heap -> last = 1;
}

#endif
