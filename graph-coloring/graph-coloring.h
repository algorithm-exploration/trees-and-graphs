#include <assert.h>
#include <stdio.h>

// Interview Cake C Unit Test Framework, based on CuTest
#include "Cake/UnitTest.h"

// Implements a set of unique keys
// Set * setNew(void);
// void setFree(Set *set);
// void setClear(Set *set);
// void setInsertPointer(Set *set, const void *ptr);
// int setContainsPointer(const Set *set, const void *ptr);
// SetIterator setIterationStart(const Set *set);
// SetIterator setIterationNext(const SetIterator si);
// int setIterationIsEnd(const SetIterator si);
// void * setIteratorGetPointerValue(const SetIterator it);
#include "Cake/Set.h"

typedef struct GraphNode {
    char *label;
    Set *neighbors;
    const char *color;
} GraphNode;

void graphNodeInitialize(GraphNode *node, const char *label)
{
    node->label = malloc(strlen(label) + 1);
    assert(node->label != NULL);
    strcpy(node->label, label);
    node->neighbors = setNew();
    node->color = NULL;
}

void graphNodeCleanup(GraphNode *node)
{
    setFree(node->neighbors);
    free(node->label);
}

GraphNode * graphNodeCreate(const char *label)
{
    GraphNode *node = malloc(sizeof(GraphNode));
    assert(node != NULL);
    graphNodeInitialize(node, label);
    return node;
}

void graphNodeFree(GraphNode *node)
{
    if (node != NULL) {
        graphNodeCleanup(node);
        free(node);
    }
}

void graphNodeAddEdge(GraphNode *node, GraphNode *neighbor)
{
    assert(node != NULL);
    assert(neighbor != NULL);
    setInsertPointer(node->neighbors, neighbor);
    setInsertPointer(neighbor->neighbors, node);
}

int colorGraph(GraphNode *graph[], size_t nodeCount, const char *colors[], size_t colorCount)
{
    // create a valid coloring for the graph
    

    return 0;
}
