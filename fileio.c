#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

Node* readGraph(char* MapName)
{
	FILE* map = fopen(MapName,"r");
	if(map == NULL)
	{
		return NULL;
	}

	int vertex_cnt;
	int read = fscanf(map,"%i",&vertex_cnt);
	if(read != 1)
	{
		fclose(map);
		return NULL;
	}

	Node* nodes = malloc(sizeof(*nodes) * vertex_cnt);
	if(nodes == NULL)
	{
		fclose(map);
		return NULL;
	}

	int edge_cnt;
	read = fscanf(map,"%i",&edge_cnt);
	if(read != 1)
	{
		fclose(map);
		free(nodes);
		return NULL;
	}

	for(unsigned int i = 0; i < vertex_cnt;i++)
	{
		int index,x_cord,y_cord;
		read = fscanf(map,"%i %i %i",&index,&x_cord,&y_cord);
		if(read != 3)
		{
			fclose(map);
			free(nodes);
			return NULL;
		}

		nodes[index].x = x_cord;
		nodes[index].y = y_cord;
	}

	EdgeTempSize = (edge_cnt / nodes + EDGEBUFFER);
    Edge* EdgeTemp = malloc(sizeof(*temp) * EdgeTempSize);

	for(unsigned int i = 0;i < edge_cnt;i++)
	{
		
	}
}
