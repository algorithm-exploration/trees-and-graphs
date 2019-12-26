#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Interview Cake C Unit Test Framework, based on CuTest
#include "Cake/UnitTest.h"

// Implements a stack
// Stack * stackNew(void);
// void stackFree(Stack *stack);
// int stackIsEmpty(const Stack *stack);
// void stackPush(Stack *stack, const void *value, size_t valueSize);
// void stackPop(Stack *stack);
// void * stackPeek(const Stack *stack);
#include "Cake/Stack.h"

typedef struct BinaryTreeNode {
    void *value;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

BinaryTreeNode * binaryTreeNodeNew(const void *value, size_t valueSize)
{
    BinaryTreeNode *node;

    node = malloc(sizeof(BinaryTreeNode));
    assert(node != NULL);

    node->value = malloc(valueSize);
    assert(node->value != NULL);
    memcpy(node->value, value, valueSize);

    node->left = NULL;
    node->right = NULL;

    return node;
}

BinaryTreeNode * binaryTreeNodeInsertLeft(BinaryTreeNode *treeRoot, const void *value, size_t valueSize)
{
    treeRoot->left = binaryTreeNodeNew(value, valueSize);
    return treeRoot->left;
}

BinaryTreeNode * binaryTreeNodeInsertRight(BinaryTreeNode *treeRoot, const void *value, size_t valueSize)
{
    treeRoot->right = binaryTreeNodeNew(value, valueSize);
    return treeRoot->right;
}

void binaryTreeNodeFree(BinaryTreeNode *treeRoot)
{
    if (treeRoot != NULL) {
        binaryTreeNodeFree(treeRoot->left);
        binaryTreeNodeFree(treeRoot->right);
        free(treeRoot->value);
        free(treeRoot);
    }
}

int isBalanced(const BinaryTreeNode *treeRoot)
{
    // determine if the tree is superbalanced
    

    return 0;
}
