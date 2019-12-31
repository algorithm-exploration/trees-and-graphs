#include <iostream>
#include <memory>
#include <stack>

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

bool isBinarySearchTree(const BinaryTreeNode* root)
{
    stack<pair<const BinaryTreeNode*, pair<int, int>>> nodeStack;
    //root node uses numeric_limits for bounds
    nodeStack.push(make_pair(root, make_pair(numeric_limits<int>::min(), numeric_limits<int>::max())));
    const BinaryTreeNode* currentNode;
    pair<int, int> currentBounds;
    
    while(!nodeStack.empty()) { //in hindsite, use a class to hold the node and its lower/upper bounds for code clarity
        currentNode = nodeStack.top().first;
        currentBounds = nodeStack.top().second;
        //comparison must be 'or equals' IOT avoid duplicates which would invalidate a binary search tree
        if(currentNode->value_ <= currentBounds.first || currentNode->value_ >= currentBounds.second) return false;
        //get rid of top node for the next iteration
        nodeStack.pop();

        //nodes inheret their limits from direct ancestor node
        if(currentNode->left_) nodeStack.push(make_pair(currentNode->left_, make_pair(currentBounds.first, currentNode->value_)));
        if(currentNode->right_) nodeStack.push(make_pair(currentNode->right_, make_pair(currentNode->value_, currentBounds.second)));
    }
    return true;
}
