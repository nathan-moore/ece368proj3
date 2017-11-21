#include <stdlib.h>
#include <stdio.h>

#include "utility.h"
#include "graph.h"

void _DownHoleHead(Heap* heap);
void _upHeap(Heap* heap);

Heap* pQueueInit(unsigned int size)
{
	Heap* rtn = malloc(sizeof(*rtn));
	if(rtn == NULL)
	{
		fprintf(stderr,"Error with malloc\n");
		exit(EXIT_FAILURE);
	}
	rtn -> heap = malloc(sizeof(*rtn -> heap) * size);
	if(rtn -> heap == NULL)
	{
		fprintf(stderr,"Error in malloc\n");
		exit(EXIT_FAILURE);
	}

	rtn -> size = size;
	rtn -> last = 0;

	return rtn;
}

//return 0 if the queue is empy
//returns 1 on success
int pop(Heap* heap,Node** toSet)
{
	if(heap -> last == 0)
	{
		return 0;
	}
	
	Node* rtn = heap -> heap[0];

	_DownHoleHead(heap);
	*toSet = rtn;
	return 1;
}

//TODO? Look up/figure out how to do
void _DownHoleHead(Heap* heap)
{
	return;
}

int addQueue(Heap* heap,Node* toAdd)
{
	if(heap -> last == heap -> size)
	{
		return 0;
	}
	heap -> heap[heap -> last] = toAdd;
	heap -> last += 1;
	_upHeap(heap);
	return 1;
}

int popAndReplace(Heap* heap,Node* toAdd,Node** rtn)
{
	
}
