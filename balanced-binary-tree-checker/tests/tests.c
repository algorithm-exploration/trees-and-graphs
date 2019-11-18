// tests

void validFullTreeTest(Test *tc)
{
    BinaryTreeNode *root, *left, *right;
    const int values[] = {50, 30, 70, 10, 40, 60, 80};

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    left = binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[2], sizeof(*values));
    binaryTreeNodeInsertLeft(left, &values[3], sizeof(*values));
    binaryTreeNodeInsertRight(left, &values[4], sizeof(*values));
    binaryTreeNodeInsertLeft(right, &values[5], sizeof(*values));
    binaryTreeNodeInsertRight(right, &values[6], sizeof(*values));

    AssertTrue(tc, isBinarySearchTree(root));
    binaryTreeNodeFree(root);
}

void bothSubtreesValidTest(Test *tc)
{
    BinaryTreeNode *root, *left, *right;
    const int values[] = {50, 30, 80, 20, 60, 70, 90};

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    left = binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[2], sizeof(*values));
    binaryTreeNodeInsertLeft(left, &values[3], sizeof(*values));
    binaryTreeNodeInsertRight(left, &values[4], sizeof(*values));
    binaryTreeNodeInsertLeft(right, &values[5], sizeof(*values));
    binaryTreeNodeInsertRight(right, &values[6], sizeof(*values));

    AssertFalse(tc, isBinarySearchTree(root));
    binaryTreeNodeFree(root);
}

void descendingLinkedListTest(Test *tc)
{
    BinaryTreeNode *root, *left;
    const int values[] = {50, 40, 30, 20, 10};

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    left = binaryTreeNodeInsertLeft(root, &values[1], sizeof(*values));
    left = binaryTreeNodeInsertLeft(left, &values[2], sizeof(*values));
    left = binaryTreeNodeInsertLeft(left, &values[3], sizeof(*values));
    binaryTreeNodeInsertLeft(left, &values[4], sizeof(*values));

    AssertTrue(tc, isBinarySearchTree(root));
    binaryTreeNodeFree(root);
}

void outOfOrderLinkedListTest(Test *tc)
{
    BinaryTreeNode *root, *right;
    const int values[] = {50,70, 60, 80};

    root = binaryTreeNodeNew(&values[0], sizeof(*values));
    right = binaryTreeNodeInsertRight(root, &values[1], sizeof(*values));
    right = binaryTreeNodeInsertRight(right, &values[2], sizeof(*values));
    binaryTreeNodeInsertRight(right, &values[3], sizeof(*values));

    AssertFalse(tc, isBinarySearchTree(root));
    binaryTreeNodeFree(root);
}

void oneNodeTreeTest(Test *tc)
{
    BinaryTreeNode *root;
    const int value = 50;

    root = binaryTreeNodeNew(&value, sizeof(value));

    AssertTrue(tc, isBinarySearchTree(root));
    binaryTreeNodeFree(root);
}

int main()
{
    TestSuite *tests = TestSuiteNew();

    SUITE_ADD_TEST(tests, validFullTreeTest);
    SUITE_ADD_TEST(tests, bothSubtreesValidTest);
    SUITE_ADD_TEST(tests, descendingLinkedListTest);
    SUITE_ADD_TEST(tests, outOfOrderLinkedListTest);
    SUITE_ADD_TEST(tests, oneNodeTreeTest);

    TestSuiteRun(tests);
    TestSuiteDelete(tests);

    return 0;
}
