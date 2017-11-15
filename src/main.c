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

	QStruct* qstruct = initQToken(argv[2]);
	for(unsigned int i = 0;i < qstruct -> cnt;i++)
	{
		Query* query = nextQuery(qstruct);
		if(query == NULL)
		{
			exit(EXIT_FAILURE);
		}
		char* path = findPath(query,graph);
	}
}
