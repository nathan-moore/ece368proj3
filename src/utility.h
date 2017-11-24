#ifndef UTILITY_HEADER
#define UTILITY_HEADER

#include "graph.h"

typedef struct _data{
	unsigned int node;
	unsigned int distance;
}data;

typedef struct _Heap{
	unsigned int size;
	unsigned int last;
	data* heap;
}Heap;


Heap* pQueueInit(unsigned int size);
int pop(Heap* heap,data* toSet);
int addQueue(Heap* Heap,int node, int distance)__attribute__((nonnull));
int popAndReplace(Heap* heap,int node,int distance,data* rtn)__attribute__((nonnull));

inline bool isEmpty(Heap* heap)
{
	return heap -> last == 1;
}

#endif
