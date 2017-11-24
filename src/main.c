#include <stdio.h>
#include <stdlib.h>

#include "fileio.h"
#include "graph.h"

int main(int argc,char** argv)
{
	if(argc != 3)
	{
		return EXIT_FAILURE;
	}

	Graph* graph = readGraph(argv[1]);
	if(graph == NULL)
	{
		printf("Error reading from file\n");
		return EXIT_FAILURE;
	}

	Query* query;
	QStruct* qstruct = initQToken(argv[2],&query);
	Heap* heap = pQueueInit(graph -> nodeCnt);

	for(unsigned int i = 0;i < qstruct -> cnt;i++)
	{
		int error = nextQuery(qstruct);
		if(error == 1)
		{
			exit(EXIT_FAILURE);
		}

		findPath(query,graph,i,heap);
	}
}
