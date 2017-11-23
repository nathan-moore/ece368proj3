#include "utility.h"
#include <stdio.h>

void printHeap(Heap* heap);

int main(void)
{
	Heap* heap = pQueueInit(10);
	int distance[] = {1,2,3,4,5,6,7,8,9,10};

	for(int i = 0; i < 10;i++)
	{
		addQueue(heap,i,distance[i]);
		printHeap(heap);
		printf("\n");
	}

	for(int i = 0; i < 11;i++)
	{
		data returned;
		int error = pop(heap,&returned);
		printHeap(heap);
		printf("%i returned %i with node of %i and distance of %i\n",i,error,returned.node,returned.distance);
		printf("\n");
	}

	return 0;
}
void printHeap(Heap* heap)
{
	for(int i = 1;i < heap -> last;i++)
	{
		printf("%i: %i %i\n",i,heap -> heap[i].node,heap -> heap[i].distance);
	}

}
