// tests

unordered_map<string, vector<string>> getNetwork()
{
    return unordered_map<string, vector<string>> {
        { "a", {"b", "c", "d"} },
        { "b", {"a", "d"} },
        { "c", {"a", "e"} },
        { "d", {"a", "b"} },
        { "e", {"c"} },
        { "f", {"g"} },
        { "g", {"f"} }
    };
}

const lest::test tests[] = {
    CASE("two hop path 1") {
        const vector<string> expected {"a", "c", "e"};
        const auto actual = getPath(getNetwork(), "a", "e");
        EXPECT(actual == expected);
    },
    CASE("two hop path 2") {
        const vector<string> expected {"d", "a", "c"};
        const auto actual = getPath(getNetwork(), "d", "c");
        EXPECT(actual == expected);
    },
    CASE("one hop path 1") {
        const vector<string> expected {"a", "c"};
        const auto actual = getPath(getNetwork(), "a", "c");
        EXPECT(actual == expected);
    },
    CASE("one hop path 2") {
        const vector<string> expected {"f", "g"};
        const auto actual = getPath(getNetwork(), "f", "g");
        EXPECT(actual == expected);
    },
    CASE("one hop path 3") {
        const vector<string> expected {"g", "f"};
        const auto actual = getPath(getNetwork(), "g", "f");
        EXPECT(actual == expected);
    },
    CASE("zero hop path") {
        const vector<string> expected {"a"};
        const auto actual = getPath(getNetwork(), "a", "a");
        EXPECT(actual == expected);
    },
    CASE("no path") {
        const vector<string> expected;
        const auto actual = getPath(getNetwork(), "a", "f");
        EXPECT(actual == expected);
    },
    CASE("start node not present") {
        EXPECT_THROWS(getPath(getNetwork(), "h", "a"));
    },
    CASE("end node not present") {
        EXPECT_THROWS(getPath(getNetwork(), "a", "h"));
    }
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
