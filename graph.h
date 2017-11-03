#ifndef GRAPH_H
#define GRAPH_H

typedef struct _node node;

//stores edge and pointers to both nodes
//done so I only have to calculate distance at most once
//distance populated upon demand
typedef struct _Edge{
	node node[2];
	int distance;
}Edge;

//intersection node
//stores location and the edges from it
typedef struct _Node{
	int x;
	int y;
	int number;
	Edge* edges;
}Node;



#endif
