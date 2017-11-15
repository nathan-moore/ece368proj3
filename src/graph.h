#ifndef GRAPH_H
#define GRAPH_H

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

typedef struct _Graph{
	Node* graph;
	int nodeCnt;
}Graph;

typedef struct _Query{
	int start;
	int finish;
}Query;

void findPath(Query* query,Graph* graph);

#endif
