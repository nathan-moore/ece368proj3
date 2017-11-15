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

typedef struct _Query{
	int start;
	int finish;
}Query;

typedef struct _QStruct{
	FILE* fp;
	int cnt;
}QStruct;

Graph* readGraph(char* MapName);
Qstruct initQToken(char* fn);
Query* nextQuery(QStruct* q);
void freeQuery(QStruct* q);

#endif
