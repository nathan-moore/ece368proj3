#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "graph.h"
#include "utility.h"

void _printRoute(Node* graph, unsigned int start);
void _recPrint(Node* graph,unsigned int start);

static inline unsigned int _getDistance(Node* n1,Node* n2);
static inline void _addEachEdgeNode(unsigned int node,unsigned int distance,Heap* heap,Node* graph);

static inline void _addEachEdgeNode(unsigned int node,unsigned int distance,Heap* heap,Node* graph)
{
	Node* from = &graph[node];
	for(unsigned int i = 0;i < from -> edge_count;i++)
	{
		Node* to = &graph[from -> edges[i].index];
		unsigned int ndist = _getDistance(from,to);
		int error = addQueue(heap,from -> edges[i].index,distance + ndist,node);
		if(error == 0)
		{
			printf("could not add to queue\n");
			exit(EXIT_FAILURE);
		}
	}
}

static inline unsigned int _getDistance(Node* n1,Node* n2)
{
	double x2 = pow(n1 -> x - n2 -> x,2);
	double y2 = pow(n1 -> y - n2 -> y,2);
	return (unsigned int) sqrt(x2 + y2);
}

void findPath(Query* query,Graph* graph,int count,Heap* heap)
{
	Node* network = graph -> graph;

	addQueue(heap,query -> start,0,query -> start);

	while(isEmpty(heap) == false)
	{
		//printHeap( heap);
		//printf("\n");
		data node;
		pop(heap,&node);

		if (node.node == query -> finish)
		{
			// printf("found the shortest? path\n");
			// printf("route backwards\n");
			printf("%d\n",node.distance);

			network[node.node].from = node.from;
			_printRoute(network,query -> finish);
			emptyQueue(heap);
			return;
		}

		//if a more efficient path hasn't been found yet
		if(network[node.node].last_visit != count)
		{
			//network[node.node].distance	= node.distance;
			network[node.node].last_visit = count;
			network[node.node].from = node.from;
			//TODO addEachEdge
			_addEachEdgeNode(node.node,node.distance,heap,network);
		}
	}
}

//TODO prints backwards
void _printRoute(Node* graph, unsigned int start)
{
	_recPrint(graph,start);
	printf("\n");
}

void _recPrint(Node* graph,unsigned int start)
{
	unsigned int next = graph[start].from;
	if(start == next)
	{
		printf("%d ",start);
		return;
	}
	_recPrint(graph,next);
	printf("%d ",start);
	return;
}
