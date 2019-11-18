// tests

#define countof(a) (sizeof(a)/sizeof((a)[0]))

void justTheRepeatedNumberTest(Test *tc)
{
    const unsigned int numbers[] = {1, 1};
    const unsigned int expected = 1;
    const unsigned int actual = findDuplicate(numbers, countof(numbers));
    AssertUnsignedIntEquals(tc, expected, actual);
}

void shortArrayTest(Test *tc)
{
    const unsigned int numbers[] = {1, 2, 3, 2};
    const unsigned int expected = 2;
    const unsigned int actual = findDuplicate(numbers, countof(numbers));
    AssertUnsignedIntEquals(tc, expected, actual);
}

void mediumArrayTest(Test *tc)
{
    const unsigned int numbers[] = {1, 2, 5, 5, 5, 5};
    const unsigned int expected = 5;
    const unsigned int actual = findDuplicate(numbers, countof(numbers));
    AssertUnsignedIntEquals(tc, expected, actual);
}

void longArrayTest(Test *tc)
{
    const unsigned int numbers[] = {4, 1, 4, 8, 3, 2, 7, 6, 5};
    const unsigned int expected = 4;
    const unsigned int actual = findDuplicate(numbers, countof(numbers));
    AssertUnsignedIntEquals(tc, expected, actual);
}

int main()
{
    TestSuite *tests = TestSuiteNew();

    SUITE_ADD_TEST(tests, justTheRepeatedNumberTest);
    SUITE_ADD_TEST(tests, shortArrayTest);
    SUITE_ADD_TEST(tests, mediumArrayTest);
    SUITE_ADD_TEST(tests, longArrayTest);

    TestSuiteRun(tests);
    TestSuiteDelete(tests);

    return 0;
}
