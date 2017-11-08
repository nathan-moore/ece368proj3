#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#define EDGEBUFFER 20

Node* readGraph(char* MapName);

#endif
