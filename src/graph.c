#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "utility.h"

inline int _getDistance(Node* n1,Node* n2);
inline void _addEachEdgeNode(int node,unsigned int distance,Heap* heap,Node* graph);

void findPath(Query* query,Graph* graph,int count,Heap* heap)
{
	Node* network = graph -> graph;


	addQueue(heap,query -> start,0);

	while(isEmpty(heap) == false)
	{
		data node;
		pop(heap,&node);

		//if a more efficient path hasn't been found yet
		if(network[node.node].last_visit != count)
		{
			network[node.node].distance	= node.distance;
			network[node.node].last_visit = count;
			//TODO addEachEdge
			_addEachEdgeNode(node.node,node.distance,heap,network);
		}
	}
}

inline void _addEachEdgeNode(int node,unsigned int distance,Heap* heap,Node* graph)
{
	Node* from = &graph[node];
	for(int i = 0;i < from -> edge_count;i++)
	{
		Node* to = &graph[from -> edges[i].index];
		int ndist = _getDistance(from,to);
		int error = addQueue(heap,from -> edges[i].index,distance + ndist);
		if(error == 0)
		{
			printf("could not add to queue\n");
			exit(EXIT_FAILURE);
		}
	}
}

inline int _getDistance(Node* n1,Node* n2)
{
	unsigned int x2 = n1 -> x << 1;
	unsigned int y2 = n1 -> y << 1;
	return (x2 + y2) >>  1;
}
