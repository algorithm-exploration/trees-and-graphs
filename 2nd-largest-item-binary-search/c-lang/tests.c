//  tests

void fullTreeTest(Test  *tc)
{
    BinaryTreeNode *root, *left, *right;
    int actual;
    const int expected = 70;
    const int values[] = {50, 30, 70 , 10, 40, 60, 80};

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    left = binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[2], sizeof(*values));
    binaryTreeNodeInsertLeft(left, &values[3], sizeof(*values));
    binaryTreeNodeInsertRight(left, &values[4], sizeof(*values));
    binaryTreeNodeInsertLeft(right, &values[5], sizeof(*values));
    binaryTreeNodeInsertRight(right, &values[6], sizeof(*values));

    actual = findSecondLargest(root);

    AssertIntEquals(tc, expected, actual);
    binaryTreeNodeFree(root);
}

void largestHasALeftChildTest(Test  *tc)
{
    BinaryTreeNode *root, *left, *right;
    int actual;
    const int expected = 60;
    const int values[] = {50, 30, 70 , 10, 40, 60};

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    left = binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[2], sizeof(*values));
    binaryTreeNodeInsertLeft(left, &values[3], sizeof(*values));
    binaryTreeNodeInsertRight(left, &values[4], sizeof(*values));
    binaryTreeNodeInsertLeft(right, &values[5], sizeof(*values));

    actual = findSecondLargest(root);

    AssertIntEquals(tc, expected, actual);
    binaryTreeNodeFree(root);
}

void largestHasALeftSubtreeTest(Test  *tc)
{
    BinaryTreeNode *root, *left, *right, *left2;
    int actual;
    const int expected = 65;
    const int values[] = {50, 30, 70 , 10, 40, 60, 55, 65, 58};

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    left = binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[2], sizeof(*values));
    binaryTreeNodeInsertLeft(left, &values[3], sizeof(*values));
    binaryTreeNodeInsertRight(left, &values[4], sizeof(*values));

    left = binaryTreeNodeInsertLeft(right, &values[5], sizeof(*values));
    left2 = binaryTreeNodeInsertLeft(left, &values[6], sizeof(*values));
    binaryTreeNodeInsertRight(left, &values[7], sizeof(*values));
    binaryTreeNodeInsertRight(left2, &values[8], sizeof(*values));

    actual = findSecondLargest(root);

    AssertIntEquals(tc, expected, actual);
    binaryTreeNodeFree(root);
}

void secondLargestIsRootNodeTest(Test  *tc)
{
    BinaryTreeNode *root, *left;
    int actual;
    const int expected = 50;
    const int values[] = {50, 30, 70, 10, 40};

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    left = binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    binaryTreeNodeInsertRight(root, &values[2], sizeof(*values));
    binaryTreeNodeInsertLeft(left, &values[3], sizeof(*values));
    binaryTreeNodeInsertRight(left, &values[4], sizeof(*values));

    actual = findSecondLargest(root);

    AssertIntEquals(tc, expected, actual);
    binaryTreeNodeFree(root);
}

void descendingLinkedListTest(Test  *tc)
{
    BinaryTreeNode *root, *left;
    int actual;
    const int expected = 40;
    const int values[] = {50, 40, 30, 20, 10};

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    left = binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    left = binaryTreeNodeInsertLeft(left, &values[2], sizeof(*values));
    left = binaryTreeNodeInsertLeft(left, &values[3], sizeof(*values));
    binaryTreeNodeInsertLeft(left, &values[4], sizeof(*values));

    actual = findSecondLargest(root);

    AssertIntEquals(tc, expected, actual);
    binaryTreeNodeFree(root);
}

void ascendingLinkedListTest(Test  *tc)
{
    BinaryTreeNode *root, *right;
    int actual;
    const int expected = 70;
    const int values[] = {50, 60, 70, 80};

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(right, &values[2], sizeof(*values));
    binaryTreeNodeInsertRight(right, &values[3], sizeof(*values));

    actual = findSecondLargest(root);

    AssertIntEquals(tc, expected, actual);
    binaryTreeNodeFree(root);
}

void callWithSingleNode(void)
{
    BinaryTreeNode *root;
    const int value = 50;

    root = binaryTreeNodeNew(&value, sizeof(value));

    findSecondLargest(root);
}

void assertionFailureWhenTreeHasOneNodeTest(Test  *tc)
{
    AssertRaises(tc, callWithSingleNode);
}

void callWithEmptyTree(void)
{
    findSecondLargest(NULL);
}

void assertionFailureWhenTreeIsEmptyTest(Test  *tc)
{
    AssertRaises(tc, callWithEmptyTree);
}

int main()
{
    TestSuite *tests = TestSuiteNew();

    SUITE_ADD_TEST(tests, fullTreeTest);
    SUITE_ADD_TEST(tests, largestHasALeftChildTest);
    SUITE_ADD_TEST(tests, largestHasALeftSubtreeTest);
    SUITE_ADD_TEST(tests, secondLargestIsRootNodeTest);
    SUITE_ADD_TEST(tests, descendingLinkedListTest);
    SUITE_ADD_TEST(tests, ascendingLinkedListTest);
    SUITE_ADD_TEST(tests, assertionFailureWhenTreeHasOneNodeTest);
    SUITE_ADD_TEST(tests, assertionFailureWhenTreeIsEmptyTest);

    TestSuiteRun(tests);
    TestSuiteDelete(tests);

    return 0;
}
