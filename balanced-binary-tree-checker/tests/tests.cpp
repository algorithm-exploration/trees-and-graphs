// tests

const lest::test tests[] = {
    CASE("Valid full tree") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(10);
        root->insertRight(70)->insertRight(80);
        root->left_->insertRight(40);
        root->right_->insertLeft(60);
        EXPECT(isBinarySearchTree(root.get()) == true);
    },
    CASE("Both subtrees valid") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(30)->insertLeft(20);
        root->insertRight(80)->insertRight(90);
        root->left_->insertRight(60);
        root->right_->insertLeft(70);
        EXPECT(isBinarySearchTree(root.get()) == false);
    },
    CASE("Descending linked list") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertLeft(40)->insertLeft(30)->insertLeft(20)->insertLeft(10);
        EXPECT(isBinarySearchTree(root.get()) == true);
    },
    CASE("Out of order linked list") {
        auto root = make_unique<BinaryTreeNode>(50);
        root->insertRight(70)->insertRight(60)->insertRight(80);
        EXPECT(isBinarySearchTree(root.get()) == false);
    },
    CASE("One node tree") {
        auto root = make_unique<BinaryTreeNode>(50);
        EXPECT(isBinarySearchTree(root.get()) == true);
    }
};

int main(int argc, char** argv)
{
    return lest::run(tests, argc, argv);
}
