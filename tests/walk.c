#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "fileio.h"

int checkEdge(unsigned int n1,unsigned int n2,Graph* g);
unsigned int getDist(unsigned int n1,unsigned int n2,Graph* g);
unsigned int* getLength(char* name,Graph* g,QStruct* q);

int main(int argc,char** argv)
{
	if(argc != 5)
	{
		printf("Error reading in file\n");
		return EXIT_FAILURE;
	}

	Query* qy;
	QStruct* q = initQToken(argv[4],&qy);
	Graph* g = readGraph(argv[1]);

	printf("Check mine\n");
	unsigned int* l1 = getLength(argv[2],g,q);
	freeQuery(q);

	printf("Check their answer\n");
	q = initQToken(argv[4],&qy);
	unsigned int* l2 = getLength(argv[3],g,q);

	for(unsigned int i = 0;i < q -> cnt;i++)
	{
		printf("Length 1: %d, Length 2: %d\n",l1[i],l2[i]);

		if( (int) l1[i] > (int) l2[i])
		{
			return 	EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

unsigned int* getLength(char* name,Graph* g,QStruct* q)
{
	FILE* file = fopen(name,"r");
	if(file == NULL)
	{
		printf("Error opening file\n");
		exit(EXIT_FAILURE);
	}

	Query* query = &q -> q;
	unsigned int* dist = calloc(q -> cnt,sizeof(*dist));

	for(unsigned int i = 0; i < q -> cnt;i++)
	{
		nextQuery(q);
		int length;
		int error = fscanf(file,"%d",&length);
		if(error != 1)
		{
			printf("Error reading from file\n");
			exit(EXIT_FAILURE);
		}


		unsigned int current;
		error = fscanf(file,"%d",&current);
		if(error != 1)
		{
			printf("Error reading from file\n");
			exit(EXIT_FAILURE);
		}

		if(current != query -> start)
		{
			fprintf(stderr,"Error parsing file\n");
			fprintf(stderr,"Expected: %d Actual: %d\n",query -> start,current);
			exit(EXIT_FAILURE);
		}

		while(current != query -> finish)
		{
			unsigned int node;
			int read = fscanf(file,"%d",&node);
			if(read == 1)
			{
				error = checkEdge(current,node,g);
				if(error != 1)
				{
					printf("Nodes %d and %d aren't connected %d\n",current,node,error);
					printf("Error in query %d\n",i);
					exit(EXIT_FAILURE);
				}
				dist[i] += getDist(current,node,g);
				current = node;
			}
		}

		if(length != (int) dist[i])
		{
			printf("Error, file distance does not match actual\n");
			printf("Query: %d,Expected: %d,Found %d\n",i,length,(int) dist[i]);
			exit(EXIT_FAILURE);
		}
	}
	return dist;
}

unsigned int getDist(unsigned int n1,unsigned int n2,Graph* g)
{
	double x = pow(g -> graph[n1].x - g -> graph[n2].x,2);
	double y = pow(g -> graph[n1].y - g -> graph[n2].y,2);
	return (unsigned int) sqrt(x + y);
}

int checkEdge(unsigned int n1,unsigned int n2,Graph* g)
{
	unsigned int i;
	for(i = 0;i < g -> graph[n1].edge_count;i++)
	{
		if(g -> graph[n1].edges[i] == n2)
		{
			break;
		}
	}

	if(i == g -> graph[n1].edge_count)
	{
		return 2;
	}

	for(i = 0;i < g -> graph[n2].edge_count;i++)
	{
		if(g -> graph[n2].edges[i] == n1)
		{
			return 1;
		}
	}

	return 3;

}
