// tests

vector<string> getColors()
{
    return vector<string> {"red", "green", "blue", "orange", "yellow", "white"};
}

bool validateGraphColoring(const vector<GraphNode*>& graph);

const lest::test tests[] = {
    CASE("line graph") {
        const auto nodeA = unique_ptr<GraphNode>(new GraphNode("A"));
        const auto nodeB = unique_ptr<GraphNode>(new GraphNode("B"));
        const auto nodeC = unique_ptr<GraphNode>(new GraphNode("C"));
        const auto nodeD = unique_ptr<GraphNode>(new GraphNode("D"));
        nodeA->addNeighbor(*nodeB);
        nodeB->addNeighbor(*nodeA);
        nodeB->addNeighbor(*nodeC);
        nodeC->addNeighbor(*nodeB);
        nodeC->addNeighbor(*nodeD);
        nodeD->addNeighbor(*nodeC);
        const vector<GraphNode*> graph { nodeA.get(), nodeB.get(), nodeC.get(), nodeD.get() };
        colorGraph(graph, getColors());
        const auto result = validateGraphColoring(graph);
        EXPECT(result == true);
    },
    CASE("separate graph") {
        const auto nodeA = unique_ptr<GraphNode>(new GraphNode("A"));
        const auto nodeB = unique_ptr<GraphNode>(new GraphNode("B"));
        const auto nodeC = unique_ptr<GraphNode>(new GraphNode("C"));
        const auto nodeD = unique_ptr<GraphNode>(new GraphNode("D"));
        nodeA->addNeighbor(*nodeB);
        nodeB->addNeighbor(*nodeA);
        nodeC->addNeighbor(*nodeD);
        nodeD->addNeighbor(*nodeC);
        const vector<GraphNode*> graph { nodeA.get(), nodeB.get(), nodeC.get(), nodeD.get() };
        colorGraph(graph, getColors());
        const auto result = validateGraphColoring(graph);
        EXPECT(result == true);
    },
    CASE("triangle graph") {
        const auto nodeA = unique_ptr<GraphNode>(new GraphNode("A"));
        const auto nodeB = unique_ptr<GraphNode>(new GraphNode("B"));
        const auto nodeC = unique_ptr<GraphNode>(new GraphNode("C"));
        nodeA->addNeighbor(*nodeB);
        nodeA->addNeighbor(*nodeC);
        nodeB->addNeighbor(*nodeA);
        nodeB->addNeighbor(*nodeC);
        nodeC->addNeighbor(*nodeA);
        nodeC->addNeighbor(*nodeB);
        const vector<GraphNode*> graph { nodeA.get(), nodeB.get(), nodeC.get() };
        colorGraph(graph, getColors());
        const auto result = validateGraphColoring(graph);
        EXPECT(result == true);
    },
    CASE("envelope graph") {
        const auto nodeA = unique_ptr<GraphNode>(new GraphNode("A"));
        const auto nodeB = unique_ptr<GraphNode>(new GraphNode("B"));
        const auto nodeC = unique_ptr<GraphNode>(new GraphNode("C"));
        const auto nodeD = unique_ptr<GraphNode>(new GraphNode("D"));
        const auto nodeE = unique_ptr<GraphNode>(new GraphNode("E"));
        nodeA->addNeighbor(*nodeB);
        nodeA->addNeighbor(*nodeC);
        nodeB->addNeighbor(*nodeA);
        nodeB->addNeighbor(*nodeC);
        nodeB->addNeighbor(*nodeD);
        nodeB->addNeighbor(*nodeE);
        nodeC->addNeighbor(*nodeA);
        nodeC->addNeighbor(*nodeB);
        nodeC->addNeighbor(*nodeD);
        nodeC->addNeighbor(*nodeE);
        nodeD->addNeighbor(*nodeB);
        nodeD->addNeighbor(*nodeC);
        nodeD->addNeighbor(*nodeE);
        nodeE->addNeighbor(*nodeB);
        nodeE->addNeighbor(*nodeC);
        nodeE->addNeighbor(*nodeD);
        const vector<GraphNode*> graph {
            nodeA.get(), nodeB.get(), nodeC.get(), nodeD.get(), nodeE.get()
        };
        colorGraph(graph, getColors());
        const auto result = validateGraphColoring(graph);
        EXPECT(result == true);
    },
    CASE("loop graph") {
        const auto nodeA = unique_ptr<GraphNode>(new GraphNode("A"));
        nodeA->addNeighbor(*nodeA);
        const vector<GraphNode*> graph { nodeA.get() };
        EXPECT_THROWS(colorGraph(graph, getColors()));
    }
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}

bool validateGraphColoring(const vector<GraphNode*>& graph)
{
    if (!all_of(graph.cbegin(), graph.cend(),
        [](const GraphNode* node) { return node->hasColor(); })) {
        // non-colored node found
        return false;
    }

    size_t maxDegree = 0;
    unordered_set<string> usedColors;

    for (const auto node : graph) {
        const auto& neighbors = node->getNeighbors();
        maxDegree = max(maxDegree, neighbors.size());
        usedColors.insert(node->getColor());
    }

    size_t allowedColorCount = maxDegree + 1;

    if (usedColors.size() > allowedColorCount) {
        // too many colors used
        return false;
    }

    for (const auto node : graph) {
        const auto& neighbors = node->getNeighbors();
        for (const auto neighbor: neighbors) {
            if (neighbor->getColor() == node->getColor()) {
                // node with same color as neighbor found
                return false;
            }
        }
    }

    return true;
}

vector<GraphNode*> makeGraphVector(const vector<unique_ptr<GraphNode>>& nodes)
{
    vector<GraphNode*> graph;
    for (const auto& node: nodes) {
        graph.push_back(node.get());
    }
    return graph;
}
