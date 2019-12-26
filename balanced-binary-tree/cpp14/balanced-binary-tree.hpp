#include <iostream>
#include <memory>
#include <stack>
#include <set>

using namespace std;

class BinaryTreeNode
{
public:
    int value_;
    BinaryTreeNode* left_;
    BinaryTreeNode* right_;

    BinaryTreeNode(int value) :
        value_(value),
        left_(nullptr),
        right_(nullptr)
    {
    }

    ~BinaryTreeNode()
    {
        delete left_;
        delete right_;
    }

    BinaryTreeNode* insertLeft(int value)
    {
        this->left_ = new BinaryTreeNode(value);
        return this->left_;
    }

    BinaryTreeNode* insertRight(int value)
    {
        this->right_ = new BinaryTreeNode(value);
        return this->right_;
    }
};

bool isBalanced(const BinaryTreeNode* treeRoot)
{
    //edge cases
    if(treeRoot == nullptr) return true;
    // determine if the tree is superbalanced
    // depth first search will give us the opportunity to quickly find disqualifying pairs of leafs
    // depth first search uses a stack vs bredth first's queue
    int depth;
    stack<pair<const BinaryTreeNode*, int>> nodes;
    nodes.push(make_pair(treeRoot,0));
    const BinaryTreeNode* currentNode;
    set<int> depthSet;
    while(!nodes.empty()) {
        currentNode=nodes.top().first;
        depth=nodes.top().second;
        nodes.pop();
        if(!currentNode->left_ && !currentNode->right_) {
            depthSet.insert(depth);
            if(abs(*(depthSet.begin()) - *(depthSet.rbegin())) > 1) {
                return false;
            }
        } else {
            if(currentNode->left_) nodes.push(make_pair(currentNode->left_, depth+1));
            if(currentNode->right_) nodes.push(make_pair(currentNode->right_, depth+1));
        }
    }
    return true;
}
