#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#define EDGEBUFFER 20
#define EDGEGROWTH 1.5

#define DEBUG 1

typedef struct _Graph{
	Node* graph;
	int nodeCnt;
}Graph;

Graph* readGraph(char* MapName);

#endif
