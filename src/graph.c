#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "graph.h"
#include "utility.h"

void _printRoute(Node* graph, unsigned int start);
void _recPrint(Node* graph,unsigned int start);
void _printInf(Query* query);

static inline unsigned int _getDistance(const Node* n1,const Node* n2);
static inline void _addEachEdgeNode(unsigned int node,unsigned int distance,Heap* heap,Node* graph,uint16_t last_visit);

static inline void _addEachEdgeNode(unsigned int node,unsigned int distance,Heap* heap,Node* graph,uint16_t last_visit)
{
	Node* from = &graph[node];
	Node* to = &graph[from -> edges[0]];

	unsigned int ndist = _getDistance(from,to);
	popAndReplace(heap,from -> edges[0],distance + ndist,node);

	for(unsigned int i = 1;i < from -> edge_count;i++)
	{
		to = &graph[from -> edges[i]];
		if(to -> last_visit != last_visit)
		{
			ndist = _getDistance(from,to);
			addQueue(heap,from -> edges[i],distance + ndist,node);
		}
	}
}

static inline unsigned int _getDistance(const Node* n1,const Node* n2)
{
	double x2 = pow(n1 -> x - n2 -> x,2);
	double y2 = pow(n1 -> y - n2 -> y,2);
	return (unsigned int) sqrt(x2 + y2);
}

void findPath(Query* query,Graph* graph,uint16_t count,Heap* heap)
{
	Node* network = graph -> graph;

	//I assume later that every query has atleast one edge
	//that would be true in every scenario except that the input edge does not have any
	if(network[query -> start].edge_count == 0)
	{
		_printInf(query);
	}
	addQueue(heap,query -> start,0,query -> start);

	while(isEmpty(heap) == false)
	{
		data node;
		peak(heap,&node);//done to minimize upheap calls

		if (node.node == query -> finish)
		{
			printf("%d\n",node.distance);

			network[node.node].from = node.from;
			_printRoute(network,query -> finish);
			emptyQueue(heap);
			return;
		}

		//if a more efficient path hasn't been found yet
		if(network[node.node].last_visit != count)
		{
			//network[node.node].distance = node.distance;
			network[node.node].last_visit = count;
			network[node.node].from = node.from;

			_addEachEdgeNode(node.node,node.distance,heap,network,count);
		}
		else
		{
			//since I peaked earlier, I have to remove the node from the heap
			popAndIgnore(heap);
		}
	}
	//couldn't find a path
	_printInf(query);
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

void _printInf(Query* query)
{
	printf("Infinity\n");
	printf("%d %d\n",query -> start,query -> finish);
}
