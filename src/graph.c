#include <stdbool.h>

#include "graph.h"
#include "utility.h"

void findPath(Query* query,Graph* graph,int count,Heap* heap)
{
	Node* network = graph -> graph;


	addQueue(heap,query -> start,0);
	graph -> graph[query -> start].distance	= 0;

	while(isEmpty(heap) == false)
	{
		data node;
		int error = pop(heap,&node);
		if(error == 0)
		{
			printf("Queue doesn't not have any more space\n");
			exit(EXIT_FAILURE);
		}

		
	}
}
