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
		printf("Could not open the file\n");
		return EXIT_FAILURE;
	}

	Node* nodes = graph -> graph;
	
	for(int i = 0;i < 10;i++)
	{
		printf("%i %i %i\n",nodes[i].x,	nodes[i].y,	nodes[i].edge_count);
		for(int j = 0;j < nodes[i].edge_count;j++)
		{
			printf("%u %i\n",nodes[i].edges[j].index,nodes[i].edges[j].distance);
		}
		printf("\n\n");
	}
}
