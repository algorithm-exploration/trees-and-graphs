// tests

#define countof(a) (sizeof(a)/sizeof((a)[0]))

struct NodeInfo {
    const char *label;
    const char *neighbors[8];
};

HashTable * createNetwork(void)
{
    static const struct NodeInfo nodes[] = {
        { "a", {"b", "c", "d", NULL} },
        { "b", {"a", "d", NULL} },
        { "c", {"a", "e", NULL} },
        { "d", {"a", "b", NULL} },
        { "e", {"c", NULL} },
        { "f", {"g", NULL} },
        { "g", {"f", NULL} },
    };

    HashTable *network = hashTableNew();
    for (size_t i = 0; i < countof(nodes); i++) {
        const struct NodeInfo *node = &nodes[i];
        size_t neighborsCount = 0;
        for (const char* const* p = node->neighbors; *p != NULL; p++, neighborsCount++);

        char **neighborsCopy = malloc((neighborsCount + 1) * sizeof(char *));
        assert(neighborsCopy != NULL);

        for (size_t j = 0; j < neighborsCount; j++) {
            const char *neighbor = node->neighbors[j];
            char *neighborCopy = malloc(strlen(neighbor) + 1);
            assert(neighborCopy != NULL);
            strcpy(neighborCopy, neighbor);
            neighborsCopy[j] = neighborCopy;
        }
        neighborsCopy[neighborsCount] = NULL;

        int result = hashTableInsertPointer(network, node->label, neighborsCopy);
        assert(result == 1);
    }
    return network;
}

void freeNeighborsEntry(void *p)
{
    char ***p1 = p;
    char **neighbors = *p1;
    while (*neighbors != NULL) {
        free(*neighbors++);
    }
    free(*p1);
    free(p);
}

void freeNetwork(HashTable *network)
{
    hashTableFreeWithDestructor(network, freeNeighborsEntry);
}

void twoHopPath1Test(Test *tc)
{
    const char *expected[] = {"a", "c", "e", NULL};
    HashTable *network = createNetwork();
    const char **actual = getPath(network, "a", "e");

    AssertPtrNotNull(tc, actual);
    if (actual == NULL) {
        freeNetwork(network);
        return;
    }

    const char **e = expected, **a = actual;
    for (; *e != NULL && *a != NULL; e++, a++) {
        AssertStrEquals(tc, *e, *a);
        if (strcmp(*e, *a)) break;
    }
    AssertPtrIsNull(tc, *e);
    AssertPtrIsNull(tc, *a);
    free(actual);
    freeNetwork(network);
}

void twoHopPath2Test(Test *tc)
{
    const char *expected[] = {"d", "a", "c", NULL};
    HashTable *network = createNetwork();
    const char **actual = getPath(network, "d", "c");

    AssertPtrNotNull(tc, actual);
    if (actual == NULL) {
        freeNetwork(network);
        return;
    }

    const char **e = expected, **a = actual;
    for (; *e != NULL && *a != NULL; e++, a++) {
        AssertStrEquals(tc, *e, *a);
        if (strcmp(*e, *a)) break;
    }
    AssertPtrIsNull(tc, *e);
    AssertPtrIsNull(tc, *a);
    free(actual);
    freeNetwork(network);
}

void oneHopPath1Test(Test *tc)
{
    const char *expected[] = {"a", "c", NULL};
    HashTable *network = createNetwork();
    const char **actual = getPath(network, "a", "c");

    AssertPtrNotNull(tc, actual);
    if (actual == NULL) {
        freeNetwork(network);
        return;
    }

    const char **e = expected, **a = actual;
    for (; *e != NULL && *a != NULL; e++, a++) {
        AssertStrEquals(tc, *e, *a);
        if (strcmp(*e, *a)) break;
    }
    AssertPtrIsNull(tc, *e);
    AssertPtrIsNull(tc, *a);
    free(actual);
    freeNetwork(network);
}

void oneHopPath2Test(Test *tc)
{
    const char *expected[] = {"f", "g", NULL};
    HashTable *network = createNetwork();
    const char **actual = getPath(network, "f", "g");

    AssertPtrNotNull(tc, actual);
    if (actual == NULL) {
        freeNetwork(network);
        return;
    }

    const char **e = expected, **a = actual;
    for (; *e != NULL && *a != NULL; e++, a++) {
        AssertStrEquals(tc, *e, *a);
        if (strcmp(*e, *a)) break;
    }
    AssertPtrIsNull(tc, *e);
    AssertPtrIsNull(tc, *a);
    free(actual);
    freeNetwork(network);
}

void oneHopPath3Test(Test *tc)
{
    const char *expected[] = {"g", "f", NULL};
    HashTable *network = createNetwork();
    const char **actual = getPath(network, "g", "f");

    AssertPtrNotNull(tc, actual);
    if (actual == NULL) {
        freeNetwork(network);
        return;
    }

    const char **e = expected, **a = actual;
    for (; *e != NULL && *a != NULL; e++, a++) {
        AssertStrEquals(tc, *e, *a);
        if (strcmp(*e, *a)) break;
    }
    AssertPtrIsNull(tc, *e);
    AssertPtrIsNull(tc, *a);
    free(actual);
    freeNetwork(network);
}

void zeroHopPathTest(Test *tc)
{
    const char *expected[] = {"a", NULL};
    HashTable *network = createNetwork();
    const char **actual = getPath(network, "a", "a");

    AssertPtrNotNull(tc, actual);
    if (actual == NULL) {
        freeNetwork(network);
        return;
    }

    const char **e = expected, **a = actual;
    for (; *e != NULL && *a != NULL; e++, a++) {
        AssertStrEquals(tc, *e, *a);
        if (strcmp(*e, *a)) break;
    }
    AssertPtrIsNull(tc, *e);
    AssertPtrIsNull(tc, *a);
    free(actual);
    freeNetwork(network);
}

void noPathTest(Test *tc)
{
    const char *expected[] = {NULL};
    HashTable *network = createNetwork();
    const char **actual = getPath(network, "a", "f");

    AssertPtrIsNull(tc, actual);
    free(actual);
    freeNetwork(network);
}

void callWithStartNodeNotPresent(void)
{
    getPath(createNetwork(), "h", "a");
}

void startNodeNotPresentTest(Test *tc)
{
    AssertRaises(tc, callWithStartNodeNotPresent);
}

void callWithEndNodeNotPresent(void)
{
    getPath(createNetwork(), "a", "h");
}

void endNodeNotPresentTest(Test *tc)
{
    AssertRaises(tc, callWithEndNodeNotPresent);
}

int main()
{
    TestSuite *tests = TestSuiteNew();

    SUITE_ADD_TEST(tests, twoHopPath1Test);
    SUITE_ADD_TEST(tests, twoHopPath2Test);
    SUITE_ADD_TEST(tests, oneHopPath1Test);
    SUITE_ADD_TEST(tests, oneHopPath2Test);
    SUITE_ADD_TEST(tests, oneHopPath3Test);
    SUITE_ADD_TEST(tests, zeroHopPathTest);
    SUITE_ADD_TEST(tests, noPathTest);
    SUITE_ADD_TEST(tests, startNodeNotPresentTest);
    SUITE_ADD_TEST(tests, endNodeNotPresentTest);

    TestSuiteRun(tests);
    TestSuiteDelete(tests);

    return 0;
}
