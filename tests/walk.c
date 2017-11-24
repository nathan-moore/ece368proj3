#include <stdio.h>

#include "fileio.h"

int checkEdge(int n1,int n2,Graph* g);

int main(int argc,char** argv)
{
	if(argc != 4)
	{
		printf("Error reading in file\n");
		return EXIT_FAILURE;
	}

	Graph* g = readGraph(argv[1]);
	double l1 = getLength(argv[2],g);
	double l2 = getLength(argv[3],g);
	if(l1 < 0 || l2 < 0)
	{
		return EXIT_FAILURE;
	}
	printf("Length 1: %lf, Length 2: %lf\n",l1,l2);
	
	return l1 <= l2;
}

double getLength(char* name,Graph* g)
{
	FILE* file = fopen(name);
	if(file == NULL)
	{
		printf("Error opening file\n");
		return EXIT_FAILURE;
	}

	int length;
	fscanf(file,"%d",&length);

	unsigned int current;
	fscanf("%d",&current);
	double dist = 0;
	do{
		unsigned int node;
		int error = fscanf("%d",&node);
		if(error == 1)
		{
			int error = checkEdge(current,node,g);
			if(error == 0)
			{
				printf("Nodes aren't connected");
				return -1;
			}
			dist += getDist(current,node,g);
		}
	}while(feof(file) == 0);

	return dist;
}

double getDist(unsigned int n1,unsigned int n2,Graph* g)
{
	double x = pow(g -> graph[n1].x - g -> graph[n2].x,2);
	double y = pow(g -> graph[n1].y - g -> graph[n2].y,2);
	return sqrt(x + y);
}

int checkEdge(unsigned int n1,unsigned int n2,Graph* g)
{
	int i;
	for(i = 0;i < g -> graph[n1].edge_count;i++)
	{
		if(g -> graph[n1].edges[i].index == n2)
		{
			break;
		}
	}

	if(i == g -> graph[n1].edge_count)
	{
		return 0;
	}

	for(i = 0;i < g -> graph[n2].edge_count;i++)
	{
		if(g -> graph[n2].edges[i].index == n1)
		{
			return 1;
		}
	}

	return 0;
	
}

