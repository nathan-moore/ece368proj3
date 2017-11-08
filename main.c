#include <stdio.h>
#include <stdlib.h>

//#include "fileio.h"
#include "graph.h"

int main(int argc,char** argv)
{
	if(argc != 3)
	{
		return EXIT_FAILURE;
	}

	Node* graph = readGraph(argv[1]);
	if(graph == NULL)
	{
		printf("Could not open the file\n");
		return EXIT_FAILURE;
	}
	
	for(int i = 0;i < 10;i++)
	{
		printf("%i %i %i\n",graph[i].x,	graph[i].y,	graph[i].edge_count);
		for(int j = 0;j < graph[i].edge_count;j++)
		{
			printf("%ui %i\n\n",graph[i].edges[j].count,graph[i].edges[j].distance);
		}
	}
}
