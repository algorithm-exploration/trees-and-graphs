#include <iostream>
#include <memory>

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

const BinaryTreeNode* getLargest(const BinaryTreeNode* root) {
    const BinaryTreeNode *currentNode;
    currentNode = root;
    while(currentNode->right_) {
        currentNode = currentNode->right_;
    } return currentNode;
}

int findSecondLargest(const BinaryTreeNode* rootNode)
{
    // handle edge cases
    if(!rootNode || (!rootNode->right_ && !rootNode->left_)) throw runtime_error("Must have two or more nodes in the tree!");
    // case: no right subtree
    if(!rootNode->right_) return rootNode->left_->value_;
    
    // get the largest element while retaining the most direct ancestor
    const BinaryTreeNode *ancestor=nullptr, *currentNode = rootNode;   
    while(currentNode->right_) {
        ancestor = currentNode;
        currentNode = currentNode->right_;
    }
    
    // if there is no left subtree of largest element, then return ancestor
    // else return the largest element in that subtree
    if(!currentNode->left_) return ancestor->value_;
    else {
        return getLargest(currentNode->left_)->value_;
    }
    return false;
}
