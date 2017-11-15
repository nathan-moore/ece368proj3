#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "fileio.h"

void _SetEdge(Node* nodes,int from,int to);

Graph* readGraph(char* MapName)
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

		if(i != index)
		{
			printf("Error matching node %d. Acual is %d.\n",i,index);
		}
		
		nodes[index].x = x_cord;
		nodes[index].y = y_cord;
	}

	unsigned int EdgeTempSize = (edge_cnt / vertex_cnt + EDGEBUFFER);
	for(unsigned int i = 0; i < vertex_cnt;i++)
	{
		nodes[i].edges = malloc(sizeof(*nodes[i].edges) * EdgeTempSize);

		if(nodes[i].edges == NULL)
		{
			fprintf(stderr,"Error with malloc\n");
		}
		nodes[i].edge_size = EdgeTempSize;
		nodes[i].edge_count = 0;
	}
	
	for(unsigned int i = 0;i < edge_cnt;i++)
	{
		int Edge1,Edge2;
		read = fscanf(map,"%i %i",&Edge1,&Edge2);
		if(read != 2)
		{
			printf("Error reading the edges from the file");
			return NULL;
		}

		if(Edge1 >= vertex_cnt)
		{
			fprintf(stderr,"Error with file %i is too large\n",Edge1);
		}
		else if (Edge2 >= vertex_cnt)
		{
			fprintf(stderr,"Error with file %i is too large\n",Edge2);
		}
		else
		{
			_SetEdge(nodes,Edge1,Edge2);
			_SetEdge(nodes,Edge2,Edge1);
		}
	}

	int Error_checking;
	read = fscanf(map,"%i",&Error_checking);
	if(read != EOF)
	{
		printf("Error, data remaining after reading in the file\n");
	}

	Graph* graph = malloc(sizeof(*graph));
	graph -> graph = nodes;
	graph -> nodeCnt = vertex_cnt;
	
	return graph;
}

void _SetEdge(Node* nodes,int from,int to)
{
	nodes[from].edges[nodes[from].edge_count].index = to;
	nodes[from].edges[nodes[from].edge_count].distance = -1;
	
	nodes[from].edge_count += 1;
	if(nodes[from].edge_count == nodes[from].edge_size)
	{
		nodes[from].edges = realloc(nodes[from].edges,(nodes[from].edge_size * EDGEGROWTH + 1) * sizeof(*nodes[from].edges));
		nodes[from].edge_size = nodes[from].edge_size * EDGEGROWTH + 1;
		if(DEBUG == 1)
		{
			printf("resized edge array\n");
		}
		if(nodes[from].edges == NULL)
		{
			fprintf(stderr,"Realloc failed\n");
			exit(EXIT_FAILURE);
		}
	}
}

QStruct* initQToken(char* fn,Query** q)
{
	QStruct* rtn = malloc(sizeof(*rtn));
	if(rtn == NULL)
	{
		fprintf(stderr,"Error with malloc");
		free(rtn);
		return NULL;
	}
	rtn -> fp = fopen(fn,"r");
	int count = fscanf(rtn -> fp,"%d",&(rtn -> cnt));
	if(count != 1)
	{
		free(rtn);
		fprintf(stderr,"error reading from file");
		return NULL;
	}
	*q = &(rtn -> q);
	return rtn;
}

int nextQuery(QStruct* q)
{
	int count= fscanf(q -> fp,"%d %d",&(q -> q.start),&(q -> q.finish));
	if (count != 2)
	{
		return 1;
	}
	return 0;
}

void freeQuery(QStruct* q)
{
	fclose(q -> fp);
	free(q);
}
