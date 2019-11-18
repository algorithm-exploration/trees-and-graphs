// tests
typedef enum GraphColoringValidationResult {
    GCVR_OK,
    GCVR_NON_COLORED_NODE,
    GCVR_TOO_MANY_COLORS,
    GCVR_NEIGHBORS_HAVE_SAME_COLOR
} GraphColoringValidationResult;

GraphColoringValidationResult validateGraphColoring(GraphNode *graph[], size_t nodeCount);

#define countof(a) (sizeof(a)/sizeof((a)[0]))

void lineGraphTest(Test *tc)
{
    GraphNode *nodeA = graphNodeCreate("A");
    GraphNode *nodeB = graphNodeCreate("B");
    GraphNode *nodeC = graphNodeCreate("C");
    GraphNode *nodeD = graphNodeCreate("D");
    graphNodeAddEdge(nodeA, nodeB);
    graphNodeAddEdge(nodeB, nodeC);
    graphNodeAddEdge(nodeC, nodeD);

    GraphNode *graph[] = { nodeA, nodeB, nodeC, nodeD };
    const char *colors[] = {"red", "green", "blue", "orange", "yellow", "white"};

    int result = colorGraph(graph, countof(graph), colors, countof(colors));
    AssertTrue(tc, result);
    if (result) {
        const enum GraphColoringValidationResult vresult =
                validateGraphColoring(graph, countof(graph));
        AssertIntEquals(tc, GCVR_OK, vresult);
    }

    graphNodeFree(nodeD);
    graphNodeFree(nodeC);
    graphNodeFree(nodeB);
    graphNodeFree(nodeA);
}

void separateGraphTest(Test *tc)
{
    GraphNode *nodeA = graphNodeCreate("A");
    GraphNode *nodeB = graphNodeCreate("B");
    GraphNode *nodeC = graphNodeCreate("C");
    GraphNode *nodeD = graphNodeCreate("D");
    graphNodeAddEdge(nodeA, nodeB);
    graphNodeAddEdge(nodeC, nodeD);

    GraphNode *graph[] = { nodeA, nodeB, nodeC, nodeD };
    const char *colors[] = {"red", "green", "blue", "orange", "yellow", "white"};

    int result = colorGraph(graph, countof(graph), colors, countof(colors));
    AssertTrue(tc, result);
    if (result) {
        const enum GraphColoringValidationResult vresult =
                validateGraphColoring(graph, countof(graph));
        AssertIntEquals(tc, GCVR_OK, vresult);
    }

    graphNodeFree(nodeD);
    graphNodeFree(nodeC);
    graphNodeFree(nodeB);
    graphNodeFree(nodeA);
}

void triangleGraphTest(Test *tc)
{
    GraphNode *nodeA = graphNodeCreate("A");
    GraphNode *nodeB = graphNodeCreate("B");
    GraphNode *nodeC = graphNodeCreate("C");
    graphNodeAddEdge(nodeA, nodeB);
    graphNodeAddEdge(nodeA, nodeC);
    graphNodeAddEdge(nodeB, nodeC);

    GraphNode *graph[] = { nodeA, nodeB, nodeC };
    const char *colors[] = {"red", "green", "blue", "orange", "yellow", "white"};

    int result = colorGraph(graph, countof(graph), colors, countof(colors));
    AssertTrue(tc, result);
    if (result) {
        const enum GraphColoringValidationResult vresult =
                validateGraphColoring(graph, countof(graph));
        AssertIntEquals(tc, GCVR_OK, vresult);
    }

    graphNodeFree(nodeC);
    graphNodeFree(nodeB);
    graphNodeFree(nodeA);
}

void envelopeGraphTest(Test *tc)
{
    GraphNode *nodeA = graphNodeCreate("A");
    GraphNode *nodeB = graphNodeCreate("B");
    GraphNode *nodeC = graphNodeCreate("C");
    GraphNode *nodeD = graphNodeCreate("D");
    GraphNode *nodeE = graphNodeCreate("E");
    graphNodeAddEdge(nodeA, nodeB);
    graphNodeAddEdge(nodeA, nodeC);
    graphNodeAddEdge(nodeB, nodeC);
    graphNodeAddEdge(nodeB, nodeD);
    graphNodeAddEdge(nodeB, nodeE);
    graphNodeAddEdge(nodeC, nodeD);
    graphNodeAddEdge(nodeC, nodeE);
    graphNodeAddEdge(nodeD, nodeE);

    GraphNode *graph[] = { nodeA, nodeB, nodeC, nodeD, nodeE };
    const char *colors[] = {"red", "green", "blue", "orange", "yellow", "white"};

    int result = colorGraph(graph, countof(graph), colors, countof(colors));
    AssertTrue(tc, result);
    if (result) {
        const enum GraphColoringValidationResult vresult =
                validateGraphColoring(graph, countof(graph));
        AssertIntEquals(tc, GCVR_OK, vresult);
    }

    graphNodeFree(nodeE);
    graphNodeFree(nodeD);
    graphNodeFree(nodeC);
    graphNodeFree(nodeB);
    graphNodeFree(nodeA);
}

void loopGraphTest(Test *tc)
{
    GraphNode *nodeA = graphNodeCreate("A");
    graphNodeAddEdge(nodeA, nodeA);

    GraphNode *graph[] = { nodeA };
    const char *colors[] = {"red", "green", "blue", "orange", "yellow", "white"};

    int result = colorGraph(graph, countof(graph), colors, countof(colors));
    AssertFalse(tc, result);

    graphNodeFree(nodeA);
}

GraphColoringValidationResult validateGraphColoring(GraphNode *graph[], size_t nodeCount)
{
    size_t i, maxDegree, actualColorCount, allowedColorCount;
    Set *usedColors;

    // check that all nodes are colored
    for (i = 0; i < nodeCount; i++) {
        const GraphNode *node = graph[i];
        if (node->color == NULL) {
            return GCVR_NON_COLORED_NODE;
        }
    }

    usedColors = setNew();
    maxDegree = 0;

    // capture used colors and determine max degree of the graph
    for (i = 0; i < nodeCount; i++) {
        const GraphNode* node = graph[i];
        size_t neighborCount = setSize(node->neighbors);

        if (neighborCount > maxDegree) {
            maxDegree = neighborCount;
        }

        setInsertPointer(usedColors, node->color);
    }

    actualColorCount = setSize(usedColors);
    setFree(usedColors);

    allowedColorCount = maxDegree + 1;

    // validate number of colors
    if (actualColorCount > allowedColorCount) {
        return GCVR_TOO_MANY_COLORS;
    }

    // check that all nodes are colored properly
    for (i = 0; i < nodeCount; i++) {
        const GraphNode* node = graph[i];
        SetIterator it;

        for (it = setIterationStart(node->neighbors); !setIterationIsEnd(it);
             it = setIterationNext(it)) {
            const GraphNode* neighbor = setIteratorGetPointerValue(it);
            if (neighbor->color == node->color) {
                return GCVR_NEIGHBORS_HAVE_SAME_COLOR;
            }
        }
    }

    return GCVR_OK;
}

int main()
{
    TestSuite *tests = TestSuiteNew();

    SUITE_ADD_TEST(tests, lineGraphTest);
    SUITE_ADD_TEST(tests, separateGraphTest);
    SUITE_ADD_TEST(tests, triangleGraphTest);
    SUITE_ADD_TEST(tests, envelopeGraphTest);
    SUITE_ADD_TEST(tests, loopGraphTest);

    TestSuiteRun(tests);
    TestSuiteDelete(tests);

    return 0;
}
