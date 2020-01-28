#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <deque>
#include <algorithm>

using namespace std;

vector<string> getPath(const unordered_map<string, vector<string>>& graph,
                       const string& startNode, const string& endNode)
{
    if(graph.find(startNode) == graph.end() || graph.find(endNode) == graph.end()) throw invalid_argument("start or end node not in graph...");
    vector<string> path;
    unordered_set<string> visited;
    deque<string> nodesToVisit;
    unordered_map<string, string> previousNode;

    visited.insert(startNode);
    nodesToVisit.push_back(startNode);
    previousNode.emplace(startNode, "");

    while(!nodesToVisit.empty()) {
        string currentNode = nodesToVisit.front();
        nodesToVisit.pop_front();
        
        if(currentNode == endNode) {
            while(!currentNode.empty()) {
                path.push_back(currentNode);
                currentNode = previousNode.find(currentNode)->second;
            } reverse(path.begin(), path.end());
            return path;
        }

        //it is not possible to use []operator on a const unordered_map
        for(const string neighbor: graph.find(currentNode)->second) {
            if(visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                nodesToVisit.push_back(neighbor);
                previousNode.emplace(neighbor, currentNode);
            }
        }
    }


    return  vector<string>();
}
