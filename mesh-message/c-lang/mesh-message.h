#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Interview Cake C Unit Test Framework, based on CuTest
#include "Cake/UnitTest.h"

// Implements a hash table that maps string keys to values
// typedef struct HashTable HashTable;
// HashTable * hashTableNew(void);
// void hashTableFree(HashTable *hashTable);
// int hashTableInsertPointer(HashTable *hashTable, const char *key, const void *value);
// void * hashTableFindPointer(const HashTable *hashTable, const char *key);
#include "Cake/HashTable.h"

// Implements a queue
// typedef struct Queue Queue;
// Queue * queueNew(void);
// void queueFree(Queue *queue);
// int queueIsEmpty(const Queue *queue);
// void queueEnqueuePointer(Queue *queue, const void *data);
// void * queueDequeuePointer(Queue *queue);
#include "Cake/Queue.h"

const char ** getPath(const HashTable *graph, const char *startNode, const char *endNode)
{
    // find the shortest route in the network between the two users
    

    return calloc(1, sizeof(const char *));
}
