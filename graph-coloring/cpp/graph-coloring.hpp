#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class GraphNode
{
private:
    string label_;
    unordered_set<GraphNode*> neighbors_;
    string color_;

public:
    GraphNode(const string& label) :
        label_(label),
        neighbors_(),
        color_()
    {
    }

    const string& getLabel() const
    {
        return label_;
    }

    const unordered_set<GraphNode*> getNeighbors() const
    {
        return neighbors_;
    }

    void addNeighbor(GraphNode& neighbor)
    {
        neighbors_.insert(&neighbor);
    }

    bool hasColor() const
    {
        return !color_.empty();
    }

    const string& getColor() const
    {
        if (hasColor()) {
            return color_;
        }
        else {
            throw logic_error("GraphNode is not marked with color");
        }
    }

    void setColor(const string& color)
    {
        color_ = color;
    }
};


//in c++ function declarations the '&' implies that the function is operating on the actual object passed in, this is similar but not equivalent to passing pointers

//here we just color the graph in O(M+N) time where M is the number of edges
void colorGraph(const vector<GraphNode*>& graph, const vector<string>& colors)
{
    for(auto node: graph) {
        const auto& neighbors = node->getNeighbors();

        //if you try to find something in a set/etc and it isn't there, you usually are returned (set/etc).end(), then we compare pointers
        if(neighbors.find(node) != neighbors.end()) 
            throw invalid_argument("There is a loop from a node to itself preventing a legal coloring of this graph...");

        unordered_set<string> illegalColors;
        for(auto neighbor: neighbors) {
            if(neighbor->hasColor()) {
                illegalColors.insert(neighbor->getColor());
            }
        }

        for(auto color: colors) {
            if(illegalColors.find(color) == illegalColors.end()) {
                node->setColor(color);
                break;
            }
        }
    }
}
