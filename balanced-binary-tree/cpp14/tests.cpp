#include "balanced-binary-tree.hpp"
#include "../../test/lest.hpp"

const lest::test tests[] = {
    CASE("Full Tree") {// make_unique is part of c++14, it constructs an object wrapped in a smart/unique pointer which ensures that when the pointer goes out of scope, the object is deleted
        auto root = make_unique<BinaryTreeNode>(5);
        root->insertLeft(8)->insertLeft(1);
        root->insertRight(6)->insertRight(4);
        root->left_->insertRight(2);
        root->right_->insertLeft(3);
        EXPECT(isBalanced(root.get()) == true);
    },
    CASE("Both leaves at the same depth") {
        auto root = make_unique<BinaryTreeNode>(3);
        root->insertLeft(4)->insertLeft(1);
        root->insertRight(2)->insertRight(9);
        EXPECT(isBalanced(root.get()) == true);
    },
    CASE("Leaf heights differ by one") {
        auto root = make_unique<BinaryTreeNode>(6);
        root->insertLeft(1);
        root->insertRight(0)->insertRight(7);
        EXPECT(isBalanced(root.get()) == true);
    },
    CASE("Leaf heights differ by two") {
        auto root = make_unique<BinaryTreeNode>(6);
        root->insertLeft(1);
        root->insertRight(0)->insertRight(7)->insertRight(8);
        EXPECT(isBalanced(root.get()) == false);
    },
    CASE("Three leaves total") {
        auto root = make_unique<BinaryTreeNode>(1);
        root->insertLeft(5);
        root->insertRight(9)->insertRight(5);
        root->right_->insertLeft(8);
        EXPECT(isBalanced(root.get()) == true);
    },
    CASE("Both subtrees superbalanced") {
        auto root = make_unique<BinaryTreeNode>(1);
        root->insertLeft(5);
        root->insertRight(9)->insertRight(5);
        root->right_->insertLeft(8)->insertLeft(7);
        EXPECT(isBalanced(root.get()) == false);
    },
    CASE("Both subtrees superbalanced two") {
        auto root = make_unique<BinaryTreeNode>(1);
        root->insertLeft(2)->insertLeft(3);
        root->left_->insertRight(7)->insertRight(8);
        root->insertRight(4)->insertRight(5)->insertRight(6)->insertRight(9);
        EXPECT(isBalanced(root.get()) == false);
    },
    CASE("Only one node") {
        auto root = make_unique<BinaryTreeNode>(1);
        EXPECT(isBalanced(root.get()) == true);
    },
    CASE("Linked list tree") {
        auto root = make_unique<BinaryTreeNode>(1);
        root->insertRight(2)->insertRight(3)->insertRight(4);
        EXPECT(isBalanced(root.get()) == true);
    },
};

int main(int argc, char** argv)
{
    if (int failures = lest::run(tests, argc, argv)) return failures;
    else return cout << "All tests passed!!!\n", EXIT_SUCCESS;
}
