#ifndef UTILITY_HEADER
#define UTILITY_HEADER

#include "graph.h"

typedef struct _Heap{
	unsigned int size;
	unsigned int last;
	Node** heap;
}Heap;

Heap* pQueueInit(unsigned int size);
int pop(Heap* heap,Node** toSet);
int addQueue(Heap* Heap,Node* toAdd)__attribute__((nonnull));
int popAndReplace(Heap* heap,Node* toAdd,Node** rtn)__attribute__((nonnull));

#endif
