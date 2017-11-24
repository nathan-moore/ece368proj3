#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "utility.h"
#include "graph.h"

void _DownHeap(Heap* heap,int current);
void _upHeap(Heap* heap,int current);

//TODO inline these 5 functions
static inline int nodeCmp(data node1,data node2);
static inline int _getLeftChild(int parent);
static inline int _getRightChild(int parent);
static inline void _swap(data* n1,data* n2);
static inline int _getParent(int child);

Heap* pQueueInit(unsigned int size)
{
	Heap* rtn = malloc(sizeof(*rtn));
	if(rtn == NULL)
	{
		fprintf(stderr,"Error with malloc\n");
		exit(EXIT_FAILURE);
	}
	rtn -> heap = malloc(sizeof(*rtn -> heap) * (1 + size));
	if(rtn -> heap == NULL)
	{
		fprintf(stderr,"Error in malloc\n");
		exit(EXIT_FAILURE);
	}

	rtn -> size = size + 1;
	rtn -> last = 1;//starts at 1 for math simplicity

	return rtn;
}

//return 0 if the queue is empy
//returns 1 on success
int pop(Heap* heap,data* toSet)
{
	if(heap -> last <= 1)
	{
		return 0;
	}

	*toSet = heap -> heap[1];
	heap -> last -= 1;
	heap -> heap[1] = heap -> heap[heap -> last];

	_DownHeap(heap,1);
	return 1;
}

int addQueue(Heap* heap,int node,int distance,int from)
{
	if(heap -> last == heap -> size)
	{
		return 0;
	}
	heap -> heap[heap -> last].node = node;
	heap -> heap[heap -> last].distance = distance;
	heap -> heap[heap -> last].from = from;

	_upHeap(heap,heap -> last);

	heap -> last += 1;

	return 1;
}

int popAndReplace(Heap* heap,int node,int distance,data* rtn)
{
	*rtn = heap -> heap[1];
	heap -> heap[1].node = node;
	heap -> heap[1].distance = distance;
	_DownHeap(heap,1);
	return 1;
}

//does down heap on
void _DownHeap(Heap* heap,int current)
{
	data* heap_arr = heap -> heap;
	int left_child = _getLeftChild(current);
	int right_child = _getRightChild(current);
	bool flag = false;
	do
	{
		flag = false;
		//prioritises the left branch first
		while(right_child < heap -> last && nodeCmp(heap_arr[current],heap_arr[left_child]) >= 0)
		{
			int location = nodeCmp(heap_arr[left_child],heap_arr[right_child]);
			if(location <= 0)
			{
				_swap(&heap_arr[current],&heap_arr[left_child]);
				current = left_child;
				left_child = _getLeftChild(current);
				right_child = _getRightChild(current);
			}
			else
			{
				_swap(&heap_arr[current],&heap_arr[right_child]);
				current = right_child;
				left_child = _getLeftChild(current);
				right_child = _getRightChild(current);
			}
		}
		//if you can swap on the right branch but not the left
		if(right_child < heap -> last && (nodeCmp(heap_arr[current],heap_arr[right_child]) >= 0))
		{
			_swap(&heap_arr[current],&heap_arr[right_child]);
			current = right_child;
			left_child = _getLeftChild(current);
			right_child = _getRightChild(current);
			flag = true;
		}
	}while(flag == true);

	//in the case where there is only one child
	if((right_child == heap -> last) && nodeCmp(heap_arr[current],heap_arr[left_child]) >= 0)
	{
		_swap(&heap_arr[current],&heap_arr[left_child]);
	}

	return;
}

void _upHeap(Heap* heap,int current)
{
	data* heap_arr = heap -> heap;
	int parent = _getParent(current);
	while(parent >= 1 && (nodeCmp(heap_arr[parent],heap_arr[current]) > 0))
	{
		_swap(&heap_arr[parent],&heap_arr[current]);
		current = parent;
		parent = _getParent(current);
	}
}

static inline int nodeCmp(data node1,data node2)
{
	return node1.distance - node2.distance;
}

static inline int _getLeftChild(int parent)
{
	return (parent * 2);
}

static inline int _getRightChild(int parent)
{
	return (parent * 2) + 1;
}

static inline void _swap(data* n1,data* n2)
{
	data temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

static inline int _getParent(int child)
{
	return child / 2;
}
