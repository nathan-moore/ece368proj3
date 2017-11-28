#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#define EDGEBUFFER 4
#define EDGEGROWTH 1.7

#define DEBUG 0

typedef struct _QStruct{
	FILE* fp;
	unsigned int cnt;
	Query q;
}QStruct;

Graph* readGraph(char* MapName);
QStruct* initQToken(char* fn,Query** q);
int nextQuery(QStruct* q);
void freeQuery(QStruct* q);

#endif
