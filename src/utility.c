#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "utility.h"
#include "graph.h"

void _DownHeap(Heap* heap,int current);
void _upHeap(Heap* heap,int current);

//TODO inline these 3 functions
int nodeCmp(Node* node1,Node* node2);
int _getLeftChild(int parrent);
int _getRightChild(int parrent);

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
	heap -> last -= 1;
	heap -> heap[0] = heap -> heap[heap -> last];

	_DownHeap(heap,0);
	*toSet = rtn;
	return 1;
}

//TODO test this
//does down heap on
void _DownHeap(Heap* heap,int current)
{
	Node** heap_arr = heap -> heap;
	int left_child = _getLeftChild(current);
	int right_child = _getRightChild(current);
	bool flag = false;
	do
	{
		flag = false;
		//prioritises the left branch first
		while(nodeCmp(heap_arr[current],heap_arr[left_child]) >= 0)
		{
			int location = nodeCmp(heap_arr[left_child],heap_arr[right_child]);
			if(location >= 0)
			{
				Node* temp = heap_arr[current];
				heap_arr[current] = heap_arr[left_child];
				heap_arr[left_child] = temp;
				current = left_child;
				left_child = _getLeftChild(current);
				right_child = _getRightChild(current);
			}
			else
			{
				Node* temp = heap_arr[current];
				heap_arr[current] = heap_arr[right_child];
				heap_arr[right_child] = temp;
				current = right_child;
				left_child = _getLeftChild(current);
				right_child = _getRightChild(current);
			}
		}
		//if you can swap on the right branch but not the left
		if(nodeCmp(heap_arr[current],heap_arr[right_child]) >= 0)
		{
			Node* temp = heap_arr[current];
			heap_arr[current] = heap_arr[right_child];
			heap_arr[right_child] = temp;
			current = right_child;
			left_child = _getLeftChild(current);
			right_child = _getRightChild(current);
			flag = true;
		}
	}while(flag == true);

	return;
}

int addQueue(Heap* heap,Node* toAdd)
{
	if(heap -> last == heap -> size)
	{
		return 0;
	}
	heap -> heap[heap -> last] = toAdd;
	_upHeap(heap,heap -> last);
	heap -> last += 1;
	return 1;
}

int popAndReplace(Heap* heap,Node* toAdd,Node** rtn)
{
	return 1;
}
