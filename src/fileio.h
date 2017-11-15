#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#define EDGEBUFFER 20
#define EDGEGROWTH 1.5

#define DEBUG 1

typedef struct _QStruct{
	FILE* fp;
	int cnt;
	Query q;
}QStruct;

Graph* readGraph(char* MapName);
QStruct* initQToken(char* fn,Query** q);
int nextQuery(QStruct* q);
void freeQuery(QStruct* q);

#endif
