// tests

void fullTreeTest(Test *tc)
{
    BinaryTreeNode *root, *left, *right;
    const int values[] = {5, 8, 6, 1, 2, 3, 5};

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    left = binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[2], sizeof(*values));
    binaryTreeNodeInsertLeft(left, &values[3], sizeof(*values));
    binaryTreeNodeInsertRight(left, &values[4], sizeof(*values));
    binaryTreeNodeInsertLeft(right, &values[5], sizeof(*values));
    binaryTreeNodeInsertRight(right, &values[6], sizeof(*values));

    AssertTrue(tc, isBalanced(root));
    binaryTreeNodeFree(root);
}

void bothLeavesAtTheSameDepthTest(Test *tc)
{
    const int values[] = {3, 4, 2, 1, 9};
    BinaryTreeNode *root, *left, *right;

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    left = binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[2], sizeof(*values));
    binaryTreeNodeInsertLeft(left, &values[3], sizeof(*values));
    binaryTreeNodeInsertRight(right, &values[4], sizeof(*values));

    AssertTrue(tc, isBalanced(root));
    binaryTreeNodeFree(root);
}

void leafHeightsDifferByOneTest(Test *tc)
{
    const int values[] = {6, 1, 0, 7};
    BinaryTreeNode *root, *right;

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[2], sizeof(*values));
    binaryTreeNodeInsertRight(right, &values[3], sizeof(*values));

    AssertTrue(tc, isBalanced(root));
    binaryTreeNodeFree(root);
}

void leafHeightsDifferByTwoTest(Test *tc)
{
    const int values[] = {6, 1, 0, 7, 8};
    BinaryTreeNode *root, *right, *right2;

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[2], sizeof(*values));
    right2 = binaryTreeNodeInsertRight(right, &values[3], sizeof(*values));
    binaryTreeNodeInsertRight(right2, &values[4], sizeof(*values));

    AssertFalse(tc, isBalanced(root));
    binaryTreeNodeFree(root);
}

void threeLeavesTotalTest(Test *tc)
{
    const int values[] = {1, 5, 9, 8, 5};
    BinaryTreeNode *root, *right;

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[2], sizeof(*values));
    binaryTreeNodeInsertLeft(right, &values[3], sizeof(*values));
    binaryTreeNodeInsertRight(right, &values[4], sizeof(*values));

    AssertTrue(tc, isBalanced(root));
    binaryTreeNodeFree(root);
}

void bothSubtreesSuperbalancedTest(Test *tc)
{
    const int values[] = {1, 5, 9, 8, 5, 7};
    BinaryTreeNode *root, *right, *left2;

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[2], sizeof(*values));
    left2 = binaryTreeNodeInsertLeft(right, &values[3], sizeof(*values));
    binaryTreeNodeInsertRight(right, &values[4], sizeof(*values));
    binaryTreeNodeInsertRight(left2, &values[5], sizeof(*values));

    AssertFalse(tc, isBalanced(root));
    binaryTreeNodeFree(root);
}

void bothSubtreesSuperbalancedTwoTest(Test *tc)
{
    const int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    BinaryTreeNode *root, *left, *right, *right2, *right3, *right4;

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    left = binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[3], sizeof(*values));
    binaryTreeNodeInsertLeft(left, &values[2], sizeof(*values));
    right2 = binaryTreeNodeInsertRight(left, &values[6], sizeof(*values));
    binaryTreeNodeInsertRight(right2, &values[7], sizeof(*values));
    right3 = binaryTreeNodeInsertRight(right, &values[4], sizeof(*values));
    right4 = binaryTreeNodeInsertRight(right3, &values[5], sizeof(*values));
    binaryTreeNodeInsertRight(right4, &values[8], sizeof(*values));

    AssertFalse(tc, isBalanced(root));
    binaryTreeNodeFree(root);
}

void onlyOneNodeTest(Test *tc)
{
    const int value = 1;
    BinaryTreeNode *root = binaryTreeNodeNew(&value, sizeof(value));

    AssertTrue(tc, isBalanced(root));
    binaryTreeNodeFree(root);
}

void linkedListTreeTest(Test *tc)
{
    const int values[] = {1, 2, 3, 4};
    BinaryTreeNode *root, *right, *right2;

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    right = binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right2 = binaryTreeNodeInsertRight(right, &values[2], sizeof(*values));
    binaryTreeNodeInsertRight(right2, &values[3], sizeof(*values));

    AssertTrue(tc, isBalanced(root));
    binaryTreeNodeFree(root);
}

int main()
{
    TestSuite *tests = TestSuiteNew();

    SUITE_ADD_TEST(tests, fullTreeTest);
    SUITE_ADD_TEST(tests, bothLeavesAtTheSameDepthTest);
    SUITE_ADD_TEST(tests, leafHeightsDifferByOneTest);
    SUITE_ADD_TEST(tests, leafHeightsDifferByTwoTest);
    SUITE_ADD_TEST(tests, threeLeavesTotalTest);
    SUITE_ADD_TEST(tests, bothSubtreesSuperbalancedTest);
    SUITE_ADD_TEST(tests, bothSubtreesSuperbalancedTwoTest);
    SUITE_ADD_TEST(tests, onlyOneNodeTest);
    SUITE_ADD_TEST(tests, linkedListTreeTest);

    TestSuiteRun(tests);
    TestSuiteDelete(tests);

    return 0;
}
