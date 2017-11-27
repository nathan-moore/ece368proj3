#ifndef GRAPH_H
#define GRAPH_H

#include <stdint.h>

#include "utility.h"

typedef struct _Heap Heap;

typedef struct _Node Node;

//stores edge and pointers to both nodes
//done so I only have to calculate distance at most once
//distance populated upon demand
typedef struct _Edge{
	uint32_t index;
	//int16_t distance;
}Edge;

//intersection node
//stores location and the edges from it
typedef struct _Node{
    int16_t x;
	int16_t y;
    uint32_t edge_count;
	uint32_t from;
	uint16_t last_visit;
	uint32_t* edges;
	//uint16_t distance;
}Node;

typedef struct _Graph{
	Node* graph;
	uint32_t nodeCnt;
}Graph;

typedef struct _Query{
	uint32_t start;
	uint32_t finish;
}Query;

void findPath(Query* query,Graph* graph,uint16_t count,Heap* heap);

#endif
