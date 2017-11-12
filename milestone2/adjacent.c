#include <stdio.h>
#include <stdlib.h>

typedef struct _Node Node;

//stores edge and pointers to both nodes
//done so I only have to calculate distance at most once
//distance populated upon demand
typedef struct _Edge{
	unsigned int index;
	int distance;
}Edge;

//intersection node
//stores location and the edges from it
typedef struct _Node{
	int x;
	int y;
	unsigned int edge_count;
	unsigned int edge_size;
	int last_visit;
	Edge* edges;
}Node;


#define EDGEBUFFER 20
#define EDGEGROWTH 1.5

#define DEBUG 1

typedef struct _Graph{
	Node* graph;
	int nodeCnt;
}Graph;

Graph* readGraph(char* MapName);

void _SetEdge(Node* nodes,int from,int to);

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		fprintf(stderr,"Improper argument count\n");
		return EXIT_FAILURE;
	}

	Graph* graph = readGraph(argv[1]);
	if(graph == NULL)
	{
		return EXIT_FAILURE;
	}

	for(unsigned int i = 0; i < graph -> nodeCnt;i++)
	{
		printf("%d:",i);
		for(unsigned int j = 0; j < graph -> graph[i].edge_count;j++)
		{
			printf(" %d",graph -> graph[i].edges[j].index);
		}
		printf("\n");
	}
}

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
