#ifndef GRAPH_H
#define GRAPH_H

#include "utility.h"

typedef struct _Heap Heap;

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
	unsigned int from;
	int last_visit;
	Edge* edges;
	//double distance;
}Node;

typedef struct _Graph{
	Node* graph;
	unsigned int nodeCnt;
}Graph;

typedef struct _Query{
	unsigned int start;
	unsigned int finish;
}Query;

void findPath(Query* query,Graph* graph,int count,Heap* heap);

#endif
