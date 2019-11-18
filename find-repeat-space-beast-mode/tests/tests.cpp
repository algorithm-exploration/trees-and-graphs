// tests

const lest::test tests[] = {
    CASE("just the repeated number") {
        const vector<unsigned int> numbers {1, 1};
        const auto expected = 1;
        const auto actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    },
    CASE("short vector") {
        const vector<unsigned int> numbers {1, 2, 3, 2};
        const auto expected = 2;
        const auto actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    },
    CASE("medium vector") {
        const vector<unsigned int> numbers {1, 2, 5, 5, 5, 5};
        const auto expected = 5;
        const auto actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    },
    CASE("long vector") {
        const vector<unsigned int> numbers {4, 1, 4, 8, 3, 2, 7, 6, 5};
        const auto expected = 4;
        const auto actual = findDuplicate(numbers);
        EXPECT(actual == expected);
    }
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
