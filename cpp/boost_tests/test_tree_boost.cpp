#include "../src/tree.h"
#include <climits>
#include <vector>
#include "output.h"

static void to_str_tree(Node* node, std::string& out) {
    if (!node) return;
    
    to_str_tree(node->left, out);
    out += std::to_string(node->data) + " ";
    to_str_tree(node->right, out);
}

BOOST_AUTO_TEST_SUITE(TreeBoostSuite)

BOOST_AUTO_TEST_CASE(PushRootAndChildren) {
    BinaryTree t;
    t.push(10);
    BOOST_TEST(t.get_root() != nullptr);
    BOOST_TEST(t.get_root()->data == 10);
    
    t.push(5);
    t.push(15);
    BOOST_TEST(t.get_root()->left->data == 5);
    BOOST_TEST(t.get_root()->right->data == 15);
}

BOOST_AUTO_TEST_CASE(PushDuplicate) {
    BinaryTree t;
    t.push(10);
    t.push(10);
    
    BOOST_TEST(t.get_root()->left == nullptr);
    BOOST_TEST(t.get_root()->right == nullptr);
}

BOOST_AUTO_TEST_CASE(PopLeaf) {
    BinaryTree t;
    t.push(10);
    t.push(5);
    t.push(15);
    
    t.pop(5);
    BOOST_TEST(t.get_root()->left == nullptr);
    
    t.pop(15);
    BOOST_TEST(t.get_root()->right == nullptr);
}

BOOST_AUTO_TEST_CASE(PopNodeWithOneChild) {
    BinaryTree t;
    t.push(10);
    t.push(5);
    t.push(3);
    
    t.pop(5);
    BOOST_TEST(t.get_root()->left->data == 3);
}

BOOST_AUTO_TEST_CASE(PopNodeWithTwoChildren) {
    BinaryTree t;
    t.push(20);
    t.push(10);
    t.push(30);
    t.push(25);
    t.push(35);
    
    t.pop(30);
    BOOST_TEST(t.get_root()->right != nullptr);
}

BOOST_AUTO_TEST_CASE(PopRoot) {
    BinaryTree t;
    t.push(10);
    t.push(5);
    
    t.pop(10);
    BOOST_TEST(t.get_root()->data == 5);
}

BOOST_AUTO_TEST_CASE(PopNonExistent) {
    BinaryTree t;
    t.push(10);
    
    OutputCapture capture;
    t.pop(999);
    std::string output = capture.get_output();
    BOOST_TEST(output == "\nЗначение для удаления не найдено\n");
}

BOOST_AUTO_TEST_CASE(PopEmptyTree) {
    BinaryTree t;
    
    OutputCapture capture;
    t.pop(10);
    std::string output = capture.get_output();
    BOOST_TEST(output == "\nОшибка удаления. Пустое дерево\n");
}

BOOST_AUTO_TEST_CASE(ClassPrintMethod) {
    BinaryTree t;
    t.push(10);
    t.push(5);
    t.push(15);
    t.push(3);
    t.push(7);
    
    OutputCapture capture;
    t.print(t.get_root());
    std::string output = capture.get_output();
    BOOST_TEST(output == "3 5 7 10 15 ");
}

BOOST_AUTO_TEST_CASE(BustTestLargeTree) {
    BinaryTree t;
    const int N = 5000;
    
    for (int i = 0; i < N; i++) {
        t.push(i);
    }
    
    BOOST_TEST(t.get_root() != nullptr);
    
    for (int i = 0; i < N; i += 500) {
        t.pop(i);
    }
}

BOOST_AUTO_TEST_CASE(BustTestExtremeValues) {
    BinaryTree t;
    
    t.push(INT_MAX);
    t.push(INT_MIN);
    t.push(0);
    
    BOOST_TEST(t.get_root()->data == INT_MAX);
    
    t.pop(INT_MAX);
    BOOST_TEST(t.get_root()->data == INT_MIN);
}

BOOST_AUTO_TEST_CASE(BustTestDestructor) {
    auto* t = new BinaryTree();
    
    for (int i = 0; i < 3000; i++) {
        t->push(i);
    }
    
    delete t;
    BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()